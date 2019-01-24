#ifndef QPID_AMQP1_0_SENDER_IMPL_H
#define QPID_AMQP1_0_SENDER_IMPL_H 1

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
#include <boost/shared_ptr.hpp>
#include "qpid/amqp/SenderImpl.h"

namespace qpid {
	namespace amqp1_0 {

		class ConnectionContext;
		class SessionContext;
		class SenderContext;
		class Session;
		class Address;
		/**
		 *
		 */
		class SenderImpl : public qpid::amqp::SenderImpl
		{
		public:
			SenderImpl(boost::shared_ptr<ConnectionContext> connection,
				boost::shared_ptr<SessionContext> session,
				boost::shared_ptr<SenderContext> sender
			);
			void send(const amqp::Message& message, bool sync);
			void close();
			void setCapacity(uint32_t);
			uint32_t getCapacity();
			uint32_t getUnsettled();
			const std::string& getName() const;
			amqp::Session getSession() const;
			amqp::Address getAddress() const;
		private:
			boost::shared_ptr<ConnectionContext> connection;
			boost::shared_ptr<SessionContext> session;
			boost::shared_ptr<SenderContext> sender;
		};
	}
}// namespace qpid::amqp1_0

#endif  /*!QPID_AMQP1_0_SENDER_IMPL_H*/
