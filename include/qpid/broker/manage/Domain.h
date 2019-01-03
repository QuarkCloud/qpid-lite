
#ifndef QPID_BROKER_MANAGE_DOMAIN_H
#define QPID_BROKER_MANAGE_DOMAIN_H 1

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

#include "qmf2/ManagementObject.h"
#include "qpid/broker/Compile.h"
#include <boost/shared_ptr.hpp>

#include <limits>

namespace qpid {
	namespace broker {
		namespace manage {


			QPID_BROKER_CLASS_EXTERN class Domain : public ::qmf2::ManagementObject
			{
			private:

				static std::string packageName;
				static std::string className;
				static uint8_t     md5Sum[MD5_LEN];


				// Properties
				std::string name;
				bool durable;
				std::string url;
				std::string mechanisms;
				std::string username;
				std::string password;

				// Statistics


			public:

				typedef boost::shared_ptr<Domain> shared_ptr;


				QPID_BROKER_EXTERN static void writeSchema(std::string& schema);
				QPID_BROKER_EXTERN void mapEncodeValues(::qpid::types::Variant::Map& map,
					bool includeProperties = true,
					bool includeStatistics = true);
				QPID_BROKER_EXTERN void mapDecodeValues(const ::qpid::types::Variant::Map& map);
				QPID_BROKER_EXTERN void doMethod(std::string&           methodName,
					const ::qpid::types::Variant::Map& inMap,
					::qpid::types::Variant::Map& outMap,
					const std::string& userId);
				QPID_BROKER_EXTERN std::string getKey() const;

				QPID_BROKER_EXTERN uint32_t writePropertiesSize() const;
				QPID_BROKER_EXTERN void readProperties(const std::string& buf);
				QPID_BROKER_EXTERN void writeProperties(std::string& buf) const;
				QPID_BROKER_EXTERN void writeStatistics(std::string& buf, bool skipHeaders = false);
				QPID_BROKER_EXTERN void doMethod(std::string& methodName,
					const std::string& inBuf,
					std::string& outBuf,
					const std::string& userId);


				writeSchemaCall_t getWriteSchemaCall() { return writeSchema; }

				// Stub for getInstChanged.  There are no statistics in this class.
				bool getInstChanged() { return false; }
				bool hasInst() { return false; }


				QPID_BROKER_EXTERN Domain(
					::qpid::broker::ManagementAgent* agent,
					::qmf2::Manageable* coreObject, const std::string& _name, bool _durable);

				QPID_BROKER_EXTERN ~Domain();

				void debugStats(const std::string& comment);



				QPID_BROKER_EXTERN static void registerSelf(
					::qpid::broker::ManagementAgent* agent);

				std::string& getPackageName() const { return packageName; }
				std::string& getClassName() const { return className; }
				uint8_t* getMd5Sum() const { return md5Sum; }

				// Method IDs

				// Accessor Methods
				inline void set_url(const std::string& val) {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					url = val;
					configChanged = true;
				}
				inline const std::string& get_url() {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					return url;
				}
				inline void set_mechanisms(const std::string& val) {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					mechanisms = val;
					configChanged = true;
				}
				inline const std::string& get_mechanisms() {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					return mechanisms;
				}
				inline void set_username(const std::string& val) {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					username = val;
					configChanged = true;
				}
				inline const std::string& get_username() {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					return username;
				}
				inline void set_password(const std::string& val) {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					password = val;
					configChanged = true;
				}
				inline const std::string& get_password() {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					return password;
				}



			};

		}
	}
}

#endif  /*!QPID_BROKER_MANAGE_DOMAIN_H*/
