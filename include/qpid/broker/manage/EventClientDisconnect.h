
#ifndef QPID_BROKER_MANAGE_EVENT_CLIENT_DISCONNECT_H
#define QPID_BROKER_MANAGE_EVENT_CLIENT_DISCONNECT_H 1

//
// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
// 
//   http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.
//

// This source file was created by a code generator.
// Please do not edit.

#include "qmf2/ManagementEvent.h"
#include "qpid/broker/Compile.h"

namespace qpid {
	namespace broker {
		namespace manage {


			QPID_BROKER_CLASS_EXTERN class EventClientDisconnect : public ::qmf2::ManagementEvent
			{
			private:
				static void writeSchema(std::string& schema);
				static uint8_t md5Sum[MD5_LEN];
				QPID_BROKER_EXTERN static std::string packageName;
				QPID_BROKER_EXTERN static std::string eventName;

				const std::string& rhost;
				const std::string& user;
				const ::qpid::types::Variant::Map& properties;


			public:
				writeSchemaCall_t getWriteSchemaCall(void) { return writeSchema; }

				QPID_BROKER_EXTERN EventClientDisconnect(const std::string& _rhost,
					const std::string& _user,
					const ::qpid::types::Variant::Map& _properties);
				QPID_BROKER_EXTERN ~EventClientDisconnect() {};

				static void registerSelf(::qpid::broker::ManagementAgent* agent);
				std::string& getPackageName() const { return packageName; }
				std::string& getEventName() const { return eventName; }
				uint8_t* getMd5Sum() const { return md5Sum; }
				uint8_t getSeverity() const { return 6; }
				QPID_BROKER_EXTERN void encode(std::string& buffer) const;
				QPID_BROKER_EXTERN void mapEncode(::qpid::types::Variant::Map& map) const;

				QPID_BROKER_EXTERN static bool match(const std::string& evt, const std::string& pkg);
				static std::pair<std::string, std::string> getFullName() {
					return std::make_pair(packageName, eventName);
				}
			};
		}
	}
}

#endif  /*!QPID_BROKER_MANAGE_EVENT_CLIENT_DISCONNECT_H*/
