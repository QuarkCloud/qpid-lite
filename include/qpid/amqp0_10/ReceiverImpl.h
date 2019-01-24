#ifndef QPID_AMQP0_10_RECEIVER_IMPL_H
#define QPID_AMQP0_10_RECEIVER_IMPL_H 1

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
#include "qpid/amqp/Address.h"
#include "qpid/amqp/Message.h"
#include "qpid/amqp/ReceiverImpl.h"
#include "qpid/client/AsyncSession.h"
#include "qpid/amqp0_10/SessionImpl.h"
#include "qpid/sys/Time.h"
#include "qpid/sys/Mutex.h"
#include <boost/intrusive_ptr.hpp>
#include <memory>

namespace qpid {
	namespace amqp0_10 {

		class AddressResolution;
		class MessageSource;

		/**
		 * A receiver implementation based on an AMQP 0-10 subscription.
		 */
		class ReceiverImpl : public qpid::amqp::ReceiverImpl
		{
		public:

			enum State { UNRESOLVED, STOPPED, STARTED, CANCELLED };

			ReceiverImpl(SessionImpl& parent, const std::string& name,
				const qpid::amqp::Address& address, bool autoDecode);

			void init(qpid::client::AsyncSession session, AddressResolution& resolver);
			bool get(qpid::amqp::Message& message, qpid::sys::MilliDuration timeout);
			qpid::amqp::Message get(qpid::sys::MilliDuration timeout);
			bool fetch(qpid::amqp::Message& message, qpid::sys::MilliDuration timeout);
			qpid::amqp::Message fetch(qpid::sys::MilliDuration timeout);
			void close();
			void start();
			void stop();
			const std::string& getName() const;
			void setCapacity(uint32_t);
			uint32_t getCapacity();
			uint32_t getAvailable();
			uint32_t getUnsettled();
			void received();
			qpid::amqp::Session getSession() const;
			bool isClosed() const;
			qpid::amqp::Address getAddress() const;

		private:
			mutable sys::Mutex lock;
			boost::intrusive_ptr<SessionImpl> parent;
			const std::string destination;
			const qpid::amqp::Address address;
			const uint32_t byteCredit;
			const bool autoDecode;
			State state;

			std::auto_ptr<MessageSource> source;
			uint32_t capacity;
			qpid::client::AsyncSession session;
			uint32_t window;

			void startFlow(const sys::Mutex::ScopedLock&); // Dummy param, call with lock held
			//implementation of public facing methods
			bool fetchImpl(qpid::amqp::Message& message, qpid::sys::MilliDuration timeout);
			bool getImpl(qpid::amqp::Message& message, qpid::sys::MilliDuration timeout);
			void closeImpl();
			void setCapacityImpl(uint32_t);

			//functors for public facing methods.
			struct Command
			{
				ReceiverImpl& impl;

				Command(ReceiverImpl& i) : impl(i) {}
			};

			struct Get : Command
			{
				qpid::amqp::Message& message;
				qpid::amqp::MilliDuration timeout;
				bool result;

				Get(ReceiverImpl& i, qpid::amqp::Message& m, qpid::sys::MilliDuration t) :
					Command(i), message(m), timeout(t), result(false) {}
				void operator()() { result = impl.getImpl(message, timeout); }
			};

			struct Fetch : Command
			{
				qpid::amqp::Message& message;
				qpid::sys::MilliDuration timeout;
				bool result;

				Fetch(ReceiverImpl& i, qpid::amqp::Message& m, qpid::amqp::MilliDuration t) :
					Command(i), message(m), timeout(t), result(false) {}
				void operator()() { result = impl.fetchImpl(message, timeout); }
			};

			struct Close : Command
			{
				Close(ReceiverImpl& i) : Command(i) {}
				void operator()() { impl.closeImpl(); }
			};

			struct SetCapacity : Command
			{
				uint32_t capacity;

				SetCapacity(ReceiverImpl& i, uint32_t c) : Command(i), capacity(c) {}
				void operator()() { impl.setCapacityImpl(capacity); }
			};

			//helper templates for some common patterns
			template <class F> void execute()
			{
				F f(*this);
				parent->execute(f);
			}

			template <class F, class P> void execute1(P p)
			{
				F f(*this, p);
				parent->execute(f);
			}
		};

	}
}// namespace qpid::amqp0_10

#endif  /*!QPID_AMQP0_10_RECEIVER_IMPL_H*/
