#ifndef QPID_AMQP0_10_SESSION_IMPL_H
#define QPID_AMQP0_10_SESSION_IMPL_H 1

/*
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 */
#include "qpid/amqp0_10/AddressResolution.h"
#include "qpid/amqp0_10/IncomingMessages.h"

#include "qpid/amqp/SessionImpl.h"
#include "qpid/amqp/Session.h"
#include "qpid/amqp/exceptions.h"

#include "qpid/driver/Session.h"
#include "qpid/framing/reply_exceptions.h"
#include "qpid/sys/ExceptionHolder.h"
#include "qpid/sys/Time.h"
#include "qpid/sys/Mutex.h"
#include <boost/intrusive_ptr.hpp>

namespace qpid {
	namespace amqp0_10 {

		class ConnectionImpl;
		class ReceiverImpl;
		class SenderImpl;

		/**
		 * Implementation of the protocol independent Session interface using
		 * AMQP 0-10.
		 */
		class SessionImpl : public qpid::amqp::SessionImpl
		{
		public:
			SessionImpl(ConnectionImpl&, bool transactional);
			void commit();
			void rollback();
			void acknowledge(bool sync);
			void reject(qpid::amqp::Message&);
			void release(qpid::amqp::Message&);
			void acknowledge(qpid::amqp::Message& msg, bool cumulative);
			void close();
			void sync(bool block);
			qpid::amqp::Sender createSender(const qpid::amqp::Address& address);
			qpid::amqp::Receiver createReceiver(const qpid::amqp::Address& address);

			qpid::amqp::Sender getSender(const std::string& name) const;
			qpid::amqp::Receiver getReceiver(const std::string& name) const;

			bool nextReceiver(qpid::amqp::Receiver& receiver, qpid::sys::MilliDuration timeout);
			qpid::amqp::Receiver nextReceiver(qpid::sys::MilliDuration timeout);

			qpid::amqp::Connection getConnection() const;
			void checkError();
			bool hasError();
			bool isTransactional() const;

			bool get(ReceiverImpl& receiver, qpid::amqp::Message& message, qpid::sys::MilliDuration timeout);

			void releasePending(const std::string& destination);
			void receiverCancelled(const std::string& name);
			void senderCancelled(const std::string& name);

			uint32_t getReceivable();
			uint32_t getReceivable(const std::string& destination);

			uint32_t getUnsettledAcks();
			uint32_t getUnsettledAcks(const std::string& destination);

			void setSession(qpid::driver::Session);

			template <class T> bool execute(T& f)
			{
				try {
					txError.raise();
					f();
					return true;
				}
				catch (const qpid::sys::TransportFailure&) {
					reconnect();
					return false;
				}
				catch (const qpid::framing::ResourceLimitExceededException& e) {
					if (backoff()) return false;
					else throw qpid::amqp::TargetCapacityExceeded(e.what());
				}
				catch (const qpid::framing::UnauthorizedAccessException& e) {
					throw qpid::amqp::UnauthorizedAccess(e.what());
				}
				catch (const qpid::framing::NotFoundException& e) {
					throw qpid::amqp::NotFound(e.what());
				}
				catch (const qpid::framing::ResourceDeletedException& e) {
					throw qpid::amqp::NotFound(e.what());
				}
				catch (const qpid::framing::SessionException& e) {
					rethrow(e);
					return false;       // Keep the compiler happy
				}
				catch (const qpid::framing::ConnectionException& e) {
					throw qpid::amqp::ConnectionError(e.what());
				}
				catch (const qpid::framing::ChannelException& e) {
					throw qpid::amqp::MessagingException(e.what());
				}
			}

			static SessionImpl& convert(qpid::amqp::Session&);
			static void rethrow(const qpid::framing::SessionException&);

		private:
			typedef std::map<std::string, qpid::amqp::Receiver> Receivers;
			typedef std::map<std::string, qpid::amqp::Sender> Senders;

			mutable qpid::sys::Mutex lock;
			boost::intrusive_ptr<ConnectionImpl> connection;
			qpid::driver::Session session;
			AddressResolution resolver;
			IncomingMessages incoming;
			Receivers receivers;
			Senders senders;
			const bool transactional;
			bool committing;
			sys::ExceptionHolder txError;

			bool accept(ReceiverImpl*, qpid::amqp::Message*, IncomingMessages::MessageTransfer&);
			bool getIncoming(IncomingMessages::Handler& handler, qpid::sys::MilliDuration timeout);
			bool getNextReceiver(qpid::amqp::Receiver* receiver, IncomingMessages::MessageTransfer& transfer);
			void reconnect();
			bool backoff();

			void commitImpl();
			void rollbackImpl();
			void acknowledgeImpl();
			void acknowledgeImpl(qpid::amqp::Message&, bool cumulative);
			void rejectImpl(qpid::amqp::Message&);
			void releaseImpl(qpid::amqp::Message&);
			void closeImpl();
			void syncImpl(bool block);
			qpid::amqp::Sender createSenderImpl(const qpid::amqp::Address& address);
			qpid::amqp::Receiver createReceiverImpl(const qpid::amqp::Address& address);
			uint32_t getReceivableImpl(const std::string* destination);
			uint32_t getUnsettledAcksImpl(const std::string* destination);

			//functors for public facing methods (allows locking and retry
			//logic to be centralised)
			struct Command
			{
				SessionImpl& impl;

				Command(SessionImpl& i) : impl(i) {}
			};

			struct Commit : Command
			{
				Commit(SessionImpl& i) : Command(i) {}
				void operator()() { impl.commitImpl(); }
			};

			struct Rollback : Command
			{
				Rollback(SessionImpl& i) : Command(i) {}
				void operator()() { impl.rollbackImpl(); }
			};

			struct Acknowledge : Command
			{
				Acknowledge(SessionImpl& i) : Command(i) {}
				void operator()() { impl.acknowledgeImpl(); }
			};

			struct Sync : Command
			{
				Sync(SessionImpl& i) : Command(i) {}
				void operator()() { impl.syncImpl(true); }
			};

			struct NonBlockingSync : Command
			{
				NonBlockingSync(SessionImpl& i) : Command(i) {}
				void operator()() { impl.syncImpl(false); }
			};

			struct Reject : Command
			{
				qpid::amqp::Message& message;

				Reject(SessionImpl& i, qpid::amqp::Message& m) : Command(i), message(m) {}
				void operator()() { impl.rejectImpl(message); }
			};

			struct Release : Command
			{
				qpid::amqp::Message& message;

				Release(SessionImpl& i, qpid::amqp::Message& m) : Command(i), message(m) {}
				void operator()() { impl.releaseImpl(message); }
			};

			struct Acknowledge2 : Command
			{
				qpid::amqp::Message& message;
				bool cumulative;

				Acknowledge2(SessionImpl& i, qpid::amqp::Message& m, bool c) : Command(i), message(m), cumulative(c) {}
				void operator()() { impl.acknowledgeImpl(message, cumulative); }
			};

			struct CreateSender;
			struct CreateReceiver;
			struct UnsettledAcks;
			struct Receivable;

			//helper templates for some common patterns
			template <class F> bool execute()
			{
				F f(*this);
				return execute(f);
			}

			template <class F> void retry()
			{
				while (!execute<F>()) {}
			}

			template <class F, class P> bool execute1(P p)
			{
				F f(*this, p);
				return execute(f);
			}

			template <class F, class R, class P> R get1(P p)
			{
				F f(*this, p);
				while (!execute(f)) {}
				return f.result;
			}
		};
	}
}// namespace qpid::amqp0_10

#endif  /*!QPID_AMQP0_10_SESSION_IMPL_H*/
