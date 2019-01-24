#ifndef QPID_AMQP1_0_SESSION_IMPL_H
#define QPID_AMQP1_0_SESSION_IMPL_H 1

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
#include "qpid/amqp/SessionImpl.h"
#include "qpid/sys/Time.h"

namespace qpid {
	namespace amqp1_0 {

		class ConnectionContext;
		class SessionContext;
		/**
		 *
		 */
		class SessionImpl : public qpid::amqp::SessionImpl
		{
		public:
			SessionImpl(boost::shared_ptr<ConnectionContext>, boost::shared_ptr<SessionContext>);
			void commit();
			void rollback();
			void acknowledge(bool sync);
			void acknowledge(amqp::Message&, bool);
			void reject(amqp::Message&);
			void release(amqp::Message&);
			void close();
			void sync(bool block);
			qpid::amqp::Sender createSender(const amqp::Address& address);
			qpid::amqp::Receiver createReceiver(const amqp::Address& address);
			bool nextReceiver(amqp::Receiver& receiver, sys::MilliDuration timeout);
			qpid::amqp::Receiver nextReceiver(sys::MilliDuration timeout);
			uint32_t getReceivable();
			uint32_t getUnsettledAcks();
			qpid::amqp::Sender getSender(const std::string& name) const;
			qpid::amqp::Receiver getReceiver(const std::string& name) const;
			qpid::amqp::Connection getConnection() const;
			void checkError();
		private:
			boost::shared_ptr<ConnectionContext> connection;
			boost::shared_ptr<SessionContext> session;
		};
	}
}// namespace qpid::amqp1_0

#endif  /*!QPID_AMQP1_0_SESSION_IMPL_H*/
