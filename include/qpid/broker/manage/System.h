
#ifndef QPID_BROKER_MANAGE_SYSTEM_H
#define QPID_BROKER_MANAGE_SYSTEM_H 1

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
#include "qpid/broker/ManagementAgent.h"
#include <boost/shared_ptr.hpp>

#include <limits>

namespace qpid {
	namespace broker {
		namespace manage {


			QPID_BROKER_CLASS_EXTERN class System : public ::qmf2::ManagementObject
			{
			private:

				static std::string packageName;
				static std::string className;
				static uint8_t     md5Sum[MD5_LEN];


				// Properties
				::qpid::types::Uuid systemId;
				std::string osName;
				std::string nodeName;
				std::string release;
				std::string version;
				std::string machine;

				// Statistics


			public:

				typedef boost::shared_ptr<System> shared_ptr;


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


				QPID_BROKER_EXTERN System(
					ManagementAgent* agent,
					::qmf2::Manageable* coreObject, const ::qpid::types::Uuid& _systemId);

				QPID_BROKER_EXTERN ~System();

				void debugStats(const std::string& comment);



				QPID_BROKER_EXTERN static void registerSelf(
					ManagementAgent* agent);

				std::string& getPackageName() const { return packageName; }
				std::string& getClassName() const { return className; }
				uint8_t* getMd5Sum() const { return md5Sum; }

				// Method IDs

				// Accessor Methods
				inline void set_osName(const std::string& val) {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					osName = val;
					configChanged = true;
				}
				inline const std::string& get_osName() {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					return osName;
				}
				inline void set_nodeName(const std::string& val) {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					nodeName = val;
					configChanged = true;
				}
				inline const std::string& get_nodeName() {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					return nodeName;
				}
				inline void set_release(const std::string& val) {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					release = val;
					configChanged = true;
				}
				inline const std::string& get_release() {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					return release;
				}
				inline void set_version(const std::string& val) {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					version = val;
					configChanged = true;
				}
				inline const std::string& get_version() {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					return version;
				}
				inline void set_machine(const std::string& val) {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					machine = val;
					configChanged = true;
				}
				inline const std::string& get_machine() {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					return machine;
				}



			};
		}
	}
}

#endif  /*!QPID_BROKER_MANAGE_SYSTEM_H*/
