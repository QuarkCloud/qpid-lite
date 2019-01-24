#ifndef QPID_AMQP0_10_ADDRESS_RESOLUTION_H
#define QPID_AMQP0_10_ADDRESS_RESOLUTION_H 1

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
#include "qpid/client/Session.h"

namespace qpid {
	namespace amqp0_10 {

		class MessageSource;
		class MessageSink;

		/**
		 * Maps from a generic Address and optional Filter to an AMQP 0-10
		 * MessageSource which will then be used by a ReceiverImpl instance
		 * created for the address.
		 */
		class AddressResolution
		{
		public:
			std::auto_ptr<MessageSource> resolveSource(qpid::client::Session session,
				const qpid::amqp::Address& address);

			std::auto_ptr<MessageSink> resolveSink(qpid::client::Session session,
				const qpid::amqp::Address& address);

			static qpid::amqp::Address convert(const qpid::framing::ReplyTo&);
			static qpid::framing::ReplyTo convert(const qpid::amqp::Address&);
			static bool is_unreliable(const qpid::amqp::Address& address);
			static bool is_reliable(const qpid::amqp::Address& address);
		private:
		};
	}
}// namespace qpid::amqp0_10

#endif  /*!QPID_AMQP0_10_ADDRESS_RESOLUTION_H*/