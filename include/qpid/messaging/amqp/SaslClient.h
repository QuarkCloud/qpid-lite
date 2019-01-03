#ifndef QPID_MESSAGING_AMQP_SASL_CLIENT_H
#define QPID_MESSAGING_AMQP_SASL_CLIENT_H 1

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
#include "qpid/messaging/Compile.h"
#include "qpid/messaging/amqp/SaslReader.h"

namespace qpid {
	namespace messaging {
		namespace amqp {

			/**
			 * Utility for decoding and encoding SASL frames by the peer acting as
			 * the SASL client.
			 */
			class SaslClient : public SaslReader
			{
			public:
				QPID_MESSAGING_EXTERN SaslClient(const std::string& id);
				QPID_MESSAGING_EXTERN virtual ~SaslClient();
				QPID_MESSAGING_EXTERN virtual void mechanisms(const std::string&) = 0;
				QPID_MESSAGING_EXTERN virtual void challenge(const std::string&) = 0;
				QPID_MESSAGING_EXTERN virtual void challenge() = 0; //null != empty string
				QPID_MESSAGING_EXTERN virtual void outcome(uint8_t result, const std::string&) = 0;
				QPID_MESSAGING_EXTERN virtual void outcome(uint8_t result) = 0;

				QPID_MESSAGING_EXTERN void init(const std::string& mechanism, const std::string* response, const std::string* hostname);
				QPID_MESSAGING_EXTERN void response(const std::string*);

			private:
				QPID_MESSAGING_EXTERN bool onStartList(uint32_t count, const CharSequence& arguments, const CharSequence&, const Descriptor* descriptor);

			};
		}
}} // namespace qpid::messaging::amqp

#endif  /*!QPID_MESSAGING_AMQP_SASL_CLIENT_H*/
