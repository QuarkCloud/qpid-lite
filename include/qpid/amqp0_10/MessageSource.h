#ifndef QPID_AMQP0_10_MESSAGE_SOURCE_H
#define QPID_AMQP0_10_MESSAGE_SOURCE_H 1

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
#include <string>
#include "qpid/driver/AsyncSession.h"

namespace qpid {
	namespace amqp0_10 {

		/**
		 * Abstraction behind which the AMQP 0-10 commands required to
		 * establish (and tear down) an incoming stream of messages from a
		 * given address are hidden.
		 */
		class MessageSource
		{
		public:
			virtual ~MessageSource() {}
			virtual void subscribe(qpid::driver::AsyncSession& session, const std::string& destination) = 0;
			virtual void cancel(qpid::driver::AsyncSession& session, const std::string& destination) = 0;

		private:
		};
	}
}// namespace qpid::amqp0_10

#endif  /*!QPID_AMQP0_10_MESSAGE_SOURCE_H*/
