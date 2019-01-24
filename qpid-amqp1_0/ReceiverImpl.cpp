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
#include "qpid/amqp1_0/ReceiverImpl.h"
#include "qpid/amqp1_0/ConnectionContext.h"
#include "qpid/amqp1_0/SessionContext.h"
#include "qpid/amqp1_0/SessionImpl.h"
#include "qpid/amqp1_0/ReceiverContext.h"
#include "qpid/amqp/exceptions.h"
#include "qpid/amqp/Message.h"
#include "qpid/amqp/Session.h"
#include "qpid/sys/Time.h"
namespace qpid {
	namespace amqp1_0 {

		ReceiverImpl::ReceiverImpl(boost::shared_ptr<ConnectionContext> c,
			boost::shared_ptr<SessionContext> s,
			boost::shared_ptr<ReceiverContext> r
		) : connection(c), session(s), receiver(r) {}


		bool ReceiverImpl::get(qpid::amqp::Message& message, qpid::sys::MilliDuration timeout)
		{
			return connection->get(session, receiver, message, timeout);
		}

		qpid::amqp::Message ReceiverImpl::get(qpid::sys::MilliDuration timeout)
		{
			qpid::amqp::Message result;
			if (!get(result, timeout)) throw qpid::amqp::NoMessageAvailable();
			return result;
		}

		bool ReceiverImpl::fetch(qpid::amqp::Message& message, qpid::sys::MilliDuration timeout)
		{
			return connection->fetch(session, receiver, message, timeout);
		}

		qpid::amqp::Message ReceiverImpl::fetch(qpid::sys::MilliDuration timeout)
		{
			qpid::amqp::Message result;
			if (!fetch(result, timeout)) throw qpid::amqp::NoMessageAvailable();
			return result;
		}

		void ReceiverImpl::setCapacity(uint32_t capacity)
		{
			connection->setCapacity(receiver, capacity);
		}

		uint32_t ReceiverImpl::getCapacity()
		{
			return connection->getCapacity(receiver);
		}

		uint32_t ReceiverImpl::getAvailable()
		{
			return connection->getAvailable(receiver);
		}

		uint32_t ReceiverImpl::getUnsettled()
		{
			return connection->getUnsettled(receiver);
		}

		void ReceiverImpl::close()
		{
			connection->detach(session, receiver);
		}

		const std::string& ReceiverImpl::getName() const
		{
			return receiver->getName();
		}

		qpid::amqp::Session ReceiverImpl::getSession() const
		{
			//create new SessionHandle instance; i.e. create new handle that shares the same context
			return qpid::amqp::Session(new SessionImpl(connection, session));
		}

		bool ReceiverImpl::isClosed() const
		{
			return connection->isClosed(session, receiver);
		}

		amqp::Address ReceiverImpl::getAddress() const
		{
			return receiver->getAddress();
		}

	}
}// namespace qpid::amqp1_0
