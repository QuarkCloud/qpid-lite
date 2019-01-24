#ifndef QPID_AMQP1_0_RECEIVER_IMPL_H
#define QPID_AMQP1_0_RECEIVER_IMPL_H 1

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
#include "qpid/amqp/ReceiverImpl.h"

namespace qpid {
	namespace amqp1_0 {

		class ConnectionContext;
		class SessionContext;
		class ReceiverContext;
		
		/**
		 *
		 */
		class ReceiverImpl : public qpid::amqp::ReceiverImpl
		{
		public:
			ReceiverImpl(boost::shared_ptr<ConnectionContext>,
				boost::shared_ptr<SessionContext>,
				boost::shared_ptr<ReceiverContext>
			);
			bool get(amqp::Message& message, qpid::sys::MilliDuration timeout);
			qpid::amqp::Message get(qpid::sys::MilliDuration timeout);
			bool fetch(amqp::Message& message, qpid::sys::MilliDuration timeout);
			qpid::amqp::Message fetch(qpid::sys::MilliDuration timeout);
			void setCapacity(uint32_t);
			uint32_t getCapacity();
			uint32_t getAvailable();
			uint32_t getUnsettled();
			void close();
			const std::string& getName() const;
			qpid::amqp::Session getSession() const;
			bool isClosed() const;
			amqp::Address getAddress() const;
		private:
			boost::shared_ptr<ConnectionContext> connection;
			boost::shared_ptr<SessionContext> session;
			boost::shared_ptr<ReceiverContext> receiver;
		};
	}
}// namespace qpid::amqp1_0

#endif  /*!QPID_AMQP1_0_RECEIVER_IMPL_H*/
