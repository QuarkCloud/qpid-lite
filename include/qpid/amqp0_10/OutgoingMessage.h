#ifndef QPID_AMQP0_10_OUTGOING_MESSAGE_H
#define QPID_AMQP0_10_OUTGOING_MESSAGE_H 1

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
#include "qpid/amqp/Message.h"
#include "qpid/driver/AsyncSession.h"
#include "qpid/driver/Completion.h"
#include "qpid/driver/Message.h"
#include "qpid/sys/Time.h"

namespace qpid {
	namespace amqp0_10 {

		class OutgoingMessage
		{
		private:
			qpid::driver::Message message;
			qpid::driver::Completion status;
			std::string subject;
			qpid::sys::AbsTime base;
			bool expired;

		public:
			OutgoingMessage();
			void convert(const qpid::amqp::Message&);
			void setSubject(const std::string& subject);
			std::string getSubject() const;
			void send(qpid::driver::AsyncSession& session, const std::string& destination, const std::string& routingKey);
			void send(qpid::driver::AsyncSession& session, const std::string& routingKey);
			bool isComplete();
			void markRedelivered();
		};

	}
}// namespace qpid::amqp0_10

#endif  /*!QPID_AMQP0_10_OUTGOING_MESSAGE_H*/
