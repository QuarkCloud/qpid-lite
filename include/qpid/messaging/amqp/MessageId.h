#ifndef QPID_MESSAGING_AMQP_MESSAGE_ID_H
#define QPID_MESSAGING_AMQP_MESSAGE_ID_H 1

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
#include "qpid/messaging/amqp/CharSequence.h"
#include "qpid/types/Variant.h"
#include "qpid/messaging/Compile.h"

namespace qpid {
	namespace messaging {
		namespace amqp {

			struct MessageId
			{
				union
				{
					CharSequence bytes;
					uint64_t ulong;
				} value;
				enum
				{
					NONE,
					BYTES,
					UUID,
					ULONG
				} type;

				QPID_MESSAGING_EXTERN MessageId();
				QPID_MESSAGING_EXTERN operator bool() const;
				QPID_MESSAGING_EXTERN std::string str() const;
				QPID_MESSAGING_EXTERN void assign(std::string&) const;
				QPID_MESSAGING_EXTERN void set(qpid::messaging::amqp::CharSequence bytes, qpid::types::VariantType t);
				QPID_MESSAGING_EXTERN void set(uint64_t ulong);

			};
		}
	}
} // namespace qpid::amqp

#endif  /*!QPID_MESSAGING_AMQP_MESSAGE_ID_H*/
