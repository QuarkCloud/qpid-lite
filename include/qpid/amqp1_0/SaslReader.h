#ifndef QPID_AMQP1_0_SASL_READER_H
#define QPID_AMQP1_0_SASL_READER_H 1

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
#include "qpid/amqp1_0/Compile.h"
#include "qpid/amqp/Encoder.h"
#include "qpid/amqp/Reader.h"
#include <string>
#include <vector>

namespace qpid {
	namespace amqp1_0 {

		/**
		 * Base for SASL client and server utilities
		 */
		class SaslReader : protected amqp::Reader
		{
		public:
			QPID_AMQP1_0_EXTERN SaslReader(const std::string& id);
			QPID_AMQP1_0_EXTERN virtual ~SaslReader();
			QPID_AMQP1_0_EXTERN std::size_t read(const char* data, size_t available);
			QPID_AMQP1_0_EXTERN std::size_t write(char* data, size_t available);
			QPID_AMQP1_0_EXTERN std::size_t readProtocolHeader(const char* buffer, std::size_t size);
			QPID_AMQP1_0_EXTERN std::size_t writeProtocolHeader(char* buffer, std::size_t size);
		protected:
			const std::string id;
			std::vector<char> buffer;
			amqp::Encoder encoder;

			void* startFrame();
			void endFrame(void*);
			QPID_AMQP1_0_EXTERN virtual bool stopReading();
		};
	}
}// namespace qpid::amqp1_0

#endif  /*!QPID_AMQP1_0_SASL_READER_H*/
