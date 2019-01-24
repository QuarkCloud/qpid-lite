#ifndef QPID_AMQP_PROTOCOL_REGISTRY_H
#define QPID_AMQP_PROTOCOL_REGISTRY_H 1

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

#include "qpid/amqp/Compile.h"
#include "qpid/amqp/ConnectionImpl.h"
#include "qpid/types/Variant.h"
#include <vector>
#include <string>

namespace qpid {
	namespace amqp {

		/**
		 * Registry for different implementations of the messaging API e.g AMQP 1.0
		 */
		class ProtocolRegistry
		{
		public:
			typedef ConnectionImpl* Factory(const std::string& url, const qpid::types::Variant::Map& options);
			typedef void Shutdown();

			static ConnectionImpl* create(const std::string& url, const qpid::types::Variant::Map& options);
			static ConnectionImpl* next(ConnectionImpl*);
			QPID_AMQP_EXTERN static void add(const std::string& name, Factory*, Shutdown*);
			QPID_AMQP_EXTERN static void shutdown();
		private:
			static ConnectionImpl* createInternal(const std::vector<std::string>& versions, const std::string& url, const qpid::types::Variant::Map& options, const std::string& error);
		};
	}
}// namespace qpid::amqp

#endif  /*!QPID_AMQP_PROTOCOL_REGISTRY_H*/
