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
#include "qpid/amqp1_0/SenderImpl.h"
#include "qpid/amqp1_0/ConnectionContext.h"
#include "qpid/amqp1_0/SessionContext.h"
#include "qpid/amqp1_0/SessionImpl.h"
#include "qpid/amqp1_0/SenderContext.h"
#include "qpid/sys/time.h"
#include "qpid/amqp/exceptions.h"
#include "qpid/amqp/Message.h"
#include "qpid/amqp/Session.h"

namespace qpid {
	namespace amqp1_0 {

		SenderImpl::SenderImpl(boost::shared_ptr<ConnectionContext> c,
			boost::shared_ptr<SessionContext> s,
			boost::shared_ptr<SenderContext> sndr
		) : connection(c), session(s), sender(sndr) {}

		void SenderImpl::send(const amqp::Message& message, bool sync)
		{
			SenderContext::Delivery* d = 0;
			connection->send(session, sender, message, sync, &d);
		}

		void SenderImpl::close()
		{
			connection->detach(session, sender);
		}

		void SenderImpl::setCapacity(uint32_t capacity)
		{
			connection->setCapacity(sender, capacity);
		}

		uint32_t SenderImpl::getCapacity()
		{
			return connection->getCapacity(sender);
		}

		uint32_t SenderImpl::getUnsettled()
		{
			return connection->getUnsettled(sender);
		}

		const std::string& SenderImpl::getName() const
		{
			return sender->getName();
		}

		qpid::amqp::Session SenderImpl::getSession() const
		{
			return qpid::amqp::Session(new SessionImpl(connection, session));
		}

		amqp::Address SenderImpl::getAddress() const
		{
			return sender->getAddress();
		}

	}
}// namespace qpid::amqp
