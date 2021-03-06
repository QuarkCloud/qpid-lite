#ifndef QPID_AMQP0_10_CODECS_INTERNAL_H
#define QPID_AMQP0_10_CODECS_INTERNAL_H 1

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
#include "qpid/amqp0_10/Compile.h"
#include "qpid/types/Variant.h"
#include "qpid/framing/Buffer.h"

namespace qpid {
	namespace amqp0_10 {
		QPID_AMQP0_10_EXTERN void encode(const qpid::types::Variant::Map& map, uint32_t len, qpid::framing::Buffer& buffer);
		QPID_AMQP0_10_EXTERN void encode(const qpid::types::Variant::List& list, uint32_t len, qpid::framing::Buffer& buffer);
		QPID_AMQP0_10_EXTERN void encode(const qpid::types::Variant& value, qpid::framing::Buffer& buffer);
		QPID_AMQP0_10_EXTERN void encode(const std::string& value, const std::string& encoding, qpid::framing::Buffer& buffer);
		QPID_AMQP0_10_EXTERN uint32_t encodedSize(const qpid::types::Variant::Map& values);
		QPID_AMQP0_10_EXTERN uint32_t encodedSize(const qpid::types::Variant::List& values);
		QPID_AMQP0_10_EXTERN uint32_t encodedSize(const std::string& value);

	}
}// namespace qpid::amqp0_10

#endif  /*!QPID_AMQP0_10_CODECS_INTERNAL_H*/
