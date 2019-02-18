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
#include "qpid/amqp0_10/SessionImpl.h"
#include "qpid/amqp0_10/ConnectionImpl.h"
#include "qpid/amqp0_10/ReceiverImpl.h"
#include "qpid/amqp0_10/SenderImpl.h"
#include "qpid/amqp0_10/MessageSource.h"
#include "qpid/amqp0_10/MessageSink.h"

#include "qpid/amqp/PrivateImplRef.h"
#include "qpid/amqp/Address.h"
#include "qpid/amqp/Connection.h"
#include "qpid/amqp/Message.h"
#include "qpid/amqp/MessageImpl.h"
#include "qpid/amqp/Sender.h"
#include "qpid/amqp/Receiver.h"
#include "qpid/amqp/Session.h"

#include "qpid/driver/SessionBaseAccess.h"
#include "qpid/driver/SessionImpl.h"

#include "qpid/framing/enum.h"
#include "qpid/framing/reply_exceptions.h"

#include "qpid/sys/Exception.h"
#include "qpid/sys/Statement.h"

#include <boost/format.hpp>
#include <boost/function.hpp>
#include <boost/intrusive_ptr.hpp>

using qpid::amqp::KeyError;
using qpid::amqp::NoMessageAvailable;
using qpid::amqp::MessagingException;
using qpid::amqp::TransactionError;
using qpid::amqp::TransactionAborted;
using qpid::amqp::TransactionUnknown;
using qpid::amqp::SessionError;
using qpid::amqp::MessageImplAccess;
using qpid::amqp::Sender;
using qpid::amqp::Receiver;

namespace qpid {
	namespace amqp0_10 {

		typedef qpid::sys::Mutex::ScopedLock ScopedLock;
		typedef qpid::sys::Mutex::ScopedUnlock ScopedUnlock;

		SessionImpl::SessionImpl(ConnectionImpl& c, bool t) :
			connection(&c), transactional(t), committing(false) {}

		bool SessionImpl::isTransactional() const
		{
			return transactional;
		}

		void SessionImpl::checkError()
		{
			ScopedLock l(lock);
			txError.raise();
			qpid::driver::SessionBaseAccess s(session);
			try {
				s.get()->assertOpen();
			}
			catch (const qpid::sys::TransportFailure&) {
				throw qpid::amqp::TransportFailure(std::string());
			}
			catch (const qpid::framing::ResourceLimitExceededException& e) {
				throw qpid::amqp::TargetCapacityExceeded(e.what());
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
				throw qpid::amqp::SessionError(e.what());
			}
			catch (const qpid::framing::ConnectionException& e) {
				throw qpid::amqp::ConnectionError(e.what());
			}
			catch (const qpid::sys::Exception& e) {
				throw qpid::amqp::MessagingException(e.what());
			}
		}

		bool SessionImpl::hasError()
		{
			ScopedLock l(lock);
			qpid::driver::SessionBaseAccess s(session);
			return s.get()->hasError();
		}

		void SessionImpl::sync(bool block)
		{
			if (block) retry<Sync>();
			else execute<NonBlockingSync>();
		}

		namespace {
			struct ScopedSet {
				bool& flag;
				ScopedSet(bool& f) : flag(f) { flag = true; }
				~ScopedSet() { flag = false; }
			};
		}

		void SessionImpl::commit()
		{
			try {
				checkError();
				ScopedSet s(committing);
				execute<Commit>();
			}
			catch (const TransactionError&) {
				assert(txError);        // Must be set by thrower of TransactionError
			}
			catch (const std::exception& e) {
				txError = new TransactionAborted(sys::Msg() << "Transaction aborted: " << e.what());
			}
			checkError();
		}

		void SessionImpl::rollback()
		{
			//If the session fails during this operation, the transaction will
			//be rolled back anyway.
			execute<Rollback>();
		}

		void SessionImpl::acknowledge(bool sync_)
		{
			//Should probably throw an exception on failure here, or indicate
			//it through a return type at least. Failure means that the
			//message may be redelivered; i.e. the application cannot delete
			//any state necessary for preventing reprocessing of the message
			execute<Acknowledge>();
			sync(sync_);
		}

		void SessionImpl::reject(qpid::amqp::Message& m)
		{
			//Possibly want to somehow indicate failure here as well. Less
			//clear need as compared to acknowledge however.
			execute1<Reject>(m);
		}

		void SessionImpl::release(qpid::amqp::Message& m)
		{
			execute1<Release>(m);
		}

		void SessionImpl::acknowledge(qpid::amqp::Message& m, bool cumulative)
		{
			//Should probably throw an exception on failure here, or indicate
			//it through a return type at least. Failure means that the
			//message may be redelivered; i.e. the application cannot delete
			//any state necessary for preventing reprocessing of the message
			Acknowledge2 ack(*this, m, cumulative);
			execute(ack);
		}

		void SessionImpl::close()
		{
			if (hasError()) {
				ScopedLock l(lock);
				senders.clear();
				receivers.clear();
			}
			else {
				Senders sCopy;
				Receivers rCopy;
				{
					ScopedLock l(lock);
					senders.swap(sCopy);
					receivers.swap(rCopy);
				}
				for (Senders::iterator i = sCopy.begin(); i != sCopy.end(); ++i)
				{
					// outside the lock, will call senderCancelled
					i->second.close();
				}
				for (Receivers::iterator i = rCopy.begin(); i != rCopy.end(); ++i)
				{
					// outside the lock, will call receiverCancelled
					i->second.close();
				}
			}
			connection->closed(*this);
			if (!hasError()) {
				ScopedLock l(lock);
				session.close();
			}
		}

		template <class T, class S> boost::intrusive_ptr<S> getImplPtr(T& t)
		{
			return boost::dynamic_pointer_cast<S>(qpid::amqp::PrivateImplRef<T>::get(t));
		}

		template <class T> void getFreeKey(std::string& key, T& map)
		{
			std::string name = key;
			int count = 1;
			for (typename T::const_iterator i = map.find(name); i != map.end(); i = map.find(name)) {
				name = (boost::format("%1%_%2%") % key % ++count).str();
			}
			key = name;
		}

		void SessionImpl::setSession(qpid::driver::Session s)
		{
			session = s;
			incoming.setSession(session);
			if (transactional) {
				session.txSelect();
			}
			for (Receivers::iterator i = receivers.begin(); i != receivers.end(); ++i) {
				getImplPtr<Receiver, ReceiverImpl>(i->second)->init(session, resolver);
			}
			for (Senders::iterator i = senders.begin(); i != senders.end(); ++i) {
				getImplPtr<Sender, SenderImpl>(i->second)->init(session, resolver);
			}
			session.sync();
		}

		struct SessionImpl::CreateReceiver : Command
		{
			qpid::amqp::Receiver result;
			const qpid::amqp::Address& address;

			CreateReceiver(SessionImpl& i, const qpid::amqp::Address& a) :
				Command(i), address(a) {}
			void operator()() { result = impl.createReceiverImpl(address); }
		};

		Receiver SessionImpl::createReceiver(const qpid::amqp::Address& address)
		{
			return get1<CreateReceiver, Receiver>(address);
		}

		Receiver SessionImpl::createReceiverImpl(const qpid::amqp::Address& address)
		{
			ScopedLock l(lock);
			std::string name = address.getName();
			getFreeKey(name, receivers);
			Receiver receiver(new ReceiverImpl(*this, name, address, connection->getAutoDecode()));
			getImplPtr<Receiver, ReceiverImpl>(receiver)->init(session, resolver);
			receivers[name] = receiver;
			return receiver;
		}

		struct SessionImpl::CreateSender : Command
		{
			qpid::amqp::Sender result;
			const qpid::amqp::Address& address;

			CreateSender(SessionImpl& i, const qpid::amqp::Address& a) :
				Command(i), address(a) {}
			void operator()() { result = impl.createSenderImpl(address); }
		};

		Sender SessionImpl::createSender(const qpid::amqp::Address& address)
		{
			return get1<CreateSender, Sender>(address);
		}

		Sender SessionImpl::createSenderImpl(const qpid::amqp::Address& address)
		{
			ScopedLock l(lock);
			std::string name = address.getName();
			getFreeKey(name, senders);
			Sender sender(new SenderImpl(*this, name, address, connection->getAutoReconnect()));
			getImplPtr<Sender, SenderImpl>(sender)->init(session, resolver);
			senders[name] = sender;
			return sender;
		}

		Sender SessionImpl::getSender(const std::string& name) const
		{
			qpid::sys::Mutex::ScopedLock l(lock);
			Senders::const_iterator i = senders.find(name);
			if (i == senders.end()) {
				throw KeyError(name);
			}
			else {
				return i->second;
			}
		}

		Receiver SessionImpl::getReceiver(const std::string& name) const
		{
			qpid::sys::Mutex::ScopedLock l(lock);
			Receivers::const_iterator i = receivers.find(name);
			if (i == receivers.end()) {
				throw KeyError(name);
			}
			else {
				return i->second;
			}
		}

		SessionImpl& SessionImpl::convert(qpid::amqp::Session& s)
		{
			boost::intrusive_ptr<SessionImpl> impl = getImplPtr<qpid::amqp::Session, SessionImpl>(s);
			if (!impl) {
				throw SessionError(QPID_MSG("Configuration error; require qpid::driver::amqp0_10::SessionImpl"));
			}
			return *impl;
		}

		namespace {

			struct IncomingMessageHandler : IncomingMessages::Handler
			{
				typedef boost::function1<bool, IncomingMessages::MessageTransfer&> Callback;
				Callback callback;
				ReceiverImpl* receiver;

				IncomingMessageHandler(Callback c) : callback(c), receiver(0) {}

				bool accept(IncomingMessages::MessageTransfer& transfer)
				{
					return callback(transfer);
				}

				bool expire(IncomingMessages::MessageTransfer& transfer)
				{
					if (receiver && receiver->getName() == transfer.getDestination() && receiver->getCapacity() > 0) {
						receiver->received();
						return true;
					}
					else {
						return false;
					}
				}

				bool isClosed()
				{
					return receiver && receiver->isClosed();
				}
			};

		}


		bool SessionImpl::getNextReceiver(Receiver* receiver, IncomingMessages::MessageTransfer& transfer)
		{
			ScopedLock l(lock);
			Receivers::const_iterator i = receivers.find(transfer.getDestination());
			if (i == receivers.end()) {
				QPID_LOG(error, "Received message for unknown destination " << transfer.getDestination());
				return false;
			}
			else {
				*receiver = i->second;
				return true;
			}
		}

		bool SessionImpl::accept(ReceiverImpl* receiver,
			qpid::amqp::Message* message,
			IncomingMessages::MessageTransfer& transfer)
		{
			if (receiver->getName() == transfer.getDestination()) {
				transfer.retrieve(message);
				receiver->received();
				return true;
			}
			else {
				return false;
			}
		}

		qpid::sys::NanoDuration adjust(qpid::sys::MilliDuration timeout)
		{
			uint64_t ms = timeout.getMilliseconds();
			if (ms < (uint64_t)(qpid::sys::TIME_INFINITE / qpid::sys::TIME_MSEC)) {
				return ms * qpid::sys::TIME_MSEC;
			}
			else {
				return qpid::sys::TIME_INFINITE;
			}
		}

		bool SessionImpl::getIncoming(IncomingMessages::Handler& handler, qpid::sys::MilliDuration timeout)
		{
			return incoming.get(handler, adjust(timeout));
		}

		bool SessionImpl::get(ReceiverImpl& receiver, qpid::amqp::Message& message, qpid::sys::MilliDuration timeout)
		{
			IncomingMessageHandler handler(boost::bind(&SessionImpl::accept, this, &receiver, &message, _1));
			handler.receiver = &receiver;
			return getIncoming(handler, timeout);
		}

		bool SessionImpl::nextReceiver(qpid::amqp::Receiver& receiver, qpid::sys::MilliDuration timeout)
		{
			while (true) {
				txError.raise();
				try {
					std::string destination;
					if (incoming.getNextDestination(destination, adjust(timeout))) {
						qpid::sys::Mutex::ScopedLock l(lock);
						Receivers::const_iterator i = receivers.find(destination);
						if (i == receivers.end()) {
							throw qpid::amqp::ReceiverError(QPID_MSG("Received message for unknown destination " << destination));
						}
						else {
							receiver = i->second;
						}
						return true;
					}
					else {
						return false;
					}
				}
				catch (sys::TransportFailure&) {
					reconnect();
				}
				catch (const qpid::framing::ResourceLimitExceededException& e) {
					if (backoff()) return false;
					else throw qpid::amqp::TargetCapacityExceeded(e.what());
				}
				catch (const qpid::framing::SessionException& e) {
					rethrow(e);
				}
				catch (const qpid::sys::ClosedException&) {
					throw qpid::amqp::SessionClosed();
				}
				catch (const qpid::framing::ConnectionException& e) {
					throw qpid::amqp::ConnectionError(e.what());
				}
				catch (const qpid::framing::ChannelException& e) {
					throw qpid::amqp::MessagingException(e.what());
				}
			}
		}

		qpid::amqp::Receiver SessionImpl::nextReceiver(qpid::sys::MilliDuration timeout)
		{
			qpid::amqp::Receiver receiver;
			if (!nextReceiver(receiver, timeout)) throw NoMessageAvailable();
			if (!receiver) throw SessionError("Bad receiver returned!");
			return receiver;
		}

		uint32_t SessionImpl::getReceivable()
		{
			return get1<Receivable, uint32_t>((const std::string*) 0);
		}
		uint32_t SessionImpl::getReceivable(const std::string& destination)
		{
			return get1<Receivable, uint32_t>(&destination);
		}

		struct SessionImpl::Receivable : Command
		{
			const std::string* destination;
			uint32_t result;

			Receivable(SessionImpl& i, const std::string* d) : Command(i), destination(d), result(0) {}
			void operator()() { result = impl.getReceivableImpl(destination); }
		};

		uint32_t SessionImpl::getReceivableImpl(const std::string* destination)
		{
			ScopedLock l(lock);
			if (destination) {
				return incoming.available(*destination);
			}
			else {
				return incoming.available();
			}
		}

		uint32_t SessionImpl::getUnsettledAcks()
		{
			return get1<UnsettledAcks, uint32_t>((const std::string*) 0);
		}

		uint32_t SessionImpl::getUnsettledAcks(const std::string& destination)
		{
			return get1<UnsettledAcks, uint32_t>(&destination);
		}

		struct SessionImpl::UnsettledAcks : Command
		{
			const std::string* destination;
			uint32_t result;

			UnsettledAcks(SessionImpl& i, const std::string* d) : Command(i), destination(d), result(0) {}
			void operator()() { result = impl.getUnsettledAcksImpl(destination); }
		};

		uint32_t SessionImpl::getUnsettledAcksImpl(const std::string* destination)
		{
			ScopedLock l(lock);
			if (destination) {
				return incoming.pendingAccept(*destination);
			}
			else {
				return incoming.pendingAccept();
			}
		}

		void SessionImpl::syncImpl(bool block)
		{
			{
				ScopedLock l(lock);
				if (block) session.sync();
				else session.flush();
			}
			//cleanup unconfirmed accept records:
			incoming.pendingAccept();
		}

		void SessionImpl::commitImpl()
		{
			ScopedLock l(lock);
			incoming.accept();
			session.txCommit();
		}

		void SessionImpl::rollbackImpl()
		{
			ScopedLock l(lock);
			for (Receivers::iterator i = receivers.begin(); i != receivers.end(); ++i) {
				getImplPtr<Receiver, ReceiverImpl>(i->second)->stop();
			}
			//ensure that stop has been processed and all previously sent
			//messages are available for release:
			session.sync();
			incoming.releaseAll();
			session.txRollback();

			for (Receivers::iterator i = receivers.begin(); i != receivers.end(); ++i) {
				getImplPtr<Receiver, ReceiverImpl>(i->second)->start();
			}
		}

		void SessionImpl::acknowledgeImpl()
		{
			if (!transactional) incoming.accept();
		}

		void SessionImpl::acknowledgeImpl(qpid::amqp::Message& m, bool cumulative)
		{
			if (!transactional) incoming.accept(MessageImplAccess::get(m).getInternalId(), cumulative);
		}

		void SessionImpl::rejectImpl(qpid::amqp::Message& m)
		{
			framing::SequenceSet set;
			set.add(MessageImplAccess::get(m).getInternalId());
			session.messageReject(set);
		}

		void SessionImpl::releaseImpl(qpid::amqp::Message& m)
		{
			framing::SequenceSet set;
			set.add(MessageImplAccess::get(m).getInternalId());
			session.messageRelease(set, true);
		}

		void SessionImpl::receiverCancelled(const std::string& name)
		{
			{
				ScopedLock l(lock);
				receivers.erase(name);
				session.sync();
				incoming.releasePending(name);
			}
			incoming.wakeup();
		}

		void SessionImpl::releasePending(const std::string& name)
		{
			ScopedLock l(lock);
			incoming.releasePending(name);
		}

		void SessionImpl::senderCancelled(const std::string& name)
		{
			ScopedLock l(lock);
			senders.erase(name);
		}

		void SessionImpl::reconnect()
		{
			if (transactional) {
				if (committing)
					txError = new TransactionUnknown("Transaction outcome unknown: transport failure");
				else
					txError = new TransactionAborted("Transaction aborted: transport failure");
				txError.raise();
			}
			connection->reopen();
		}

		bool SessionImpl::backoff()
		{
			return connection->backoff();
		}

		qpid::amqp::Connection SessionImpl::getConnection() const
		{
			return qpid::amqp::Connection(connection.get());
		}

		void SessionImpl::rethrow(const qpid::framing::SessionException& e) {
			switch (e.code) {
			case framing::execution::ERROR_CODE_NOT_ALLOWED:
			case framing::execution::ERROR_CODE_UNAUTHORIZED_ACCESS: throw amqp::UnauthorizedAccess(e.what());

			case framing::execution::ERROR_CODE_NOT_FOUND:
			case framing::execution::ERROR_CODE_RESOURCE_DELETED: throw amqp::NotFound(e.what());

			default: throw SessionError(e.what());
			}
		}

	}
}// namespace qpid::amqp0_10
