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
#include "qpid/amqp1_0/SessionImpl.h"
#include "qpid/amqp1_0/ConnectionContext.h"
#include "qpid/amqp1_0/ConnectionImpl.h"
#include "qpid/amqp1_0/ReceiverContext.h"
#include "qpid/amqp1_0/ReceiverImpl.h"
#include "qpid/amqp1_0/SenderContext.h"
#include "qpid/amqp1_0/SenderImpl.h"
#include "qpid/amqp1_0/SessionContext.h"
#include "qpid/amqp/Connection.h"
#include "qpid/amqp/exceptions.h"
#include "qpid/amqp/Receiver.h"
#include "qpid/amqp/Sender.h"
#include "qpid/amqp/Session.h"
#include "qpid/sys/Statement.h"
#include "qpid/sys/Time.h"

namespace qpid {
	namespace amqp1_0 {

		SessionImpl::SessionImpl(boost::shared_ptr<ConnectionContext> c, boost::shared_ptr<SessionContext> s) :
			connection(c), session(s) {}

		void SessionImpl::commit()
		{
			connection->commit(session);
		}

		void SessionImpl::rollback()
		{
			connection->rollback(session);
		}

		void SessionImpl::acknowledge(bool /*sync*/)
		{
			connection->acknowledge(session, 0, false);
		}

		void SessionImpl::acknowledge(qpid::amqp::Message& msg, bool cumulative)
		{
			connection->acknowledge(session, &msg, cumulative);
		}

		void SessionImpl::reject(qpid::amqp::Message& msg)
		{
			connection->nack(session, msg, true);
		}

		void SessionImpl::release(qpid::amqp::Message& msg)
		{
			connection->nack(session, msg, false);
		}

		void SessionImpl::close()
		{
			connection->endSession(session);
		}

		void SessionImpl::sync(bool block)
		{
			if (block) {
				connection->sync(session);
			}
		}

		qpid::amqp::Sender SessionImpl::createSender(const qpid::amqp::Address& address)
		{
			boost::shared_ptr<SenderContext> sender = connection->createSender(session, address);
			return qpid::amqp::Sender(new SenderImpl(connection, session, sender));
		}

		qpid::amqp::Receiver SessionImpl::createReceiver(const qpid::amqp::Address& address)
		{
			boost::shared_ptr<ReceiverContext> receiver = connection->createReceiver(session, address);
			return qpid::amqp::Receiver(new ReceiverImpl(connection, session, receiver));
		}

		bool SessionImpl::nextReceiver(amqp::Receiver& receiver, sys::MilliDuration timeout)
		{
			boost::shared_ptr<ReceiverContext> r = connection->nextReceiver(session, timeout);
			if (r) {
				//TODO: cache handles in this case to avoid frequent allocation
				receiver = qpid::amqp::Receiver(new ReceiverImpl(connection, session, r));
				return true;
			}
			else {
				return false;
			}
		}

		qpid::amqp::Receiver SessionImpl::nextReceiver(sys::MilliDuration timeout)
		{
			qpid::amqp::Receiver r;
			if (nextReceiver(r, timeout)) return r;
			else throw qpid::amqp::NoMessageAvailable();
		}

		uint32_t SessionImpl::getReceivable()
		{
			return session->getReceivable();
		}

		uint32_t SessionImpl::getUnsettledAcks()
		{
			return session->getUnsettledAcks();
		}

		amqp::Sender SessionImpl::getSender(const std::string& name) const
		{
			return qpid::amqp::Sender(new SenderImpl(connection, session, connection->getSender(session, name)));
		}

		amqp::Receiver SessionImpl::getReceiver(const std::string& name) const
		{
			return qpid::amqp::Receiver(new ReceiverImpl(connection, session, connection->getReceiver(session, name)));
		}

		amqp::Connection SessionImpl::getConnection() const
		{
			return qpid::amqp::Connection(new ConnectionImpl(connection));
		}

		void SessionImpl::checkError()
		{

		}
	}
}// namespace qpid::amqp
