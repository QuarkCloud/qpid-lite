
#ifndef QPID_BROKER_MANAGE_BINDING_H
#define QPID_BROKER_MANAGE_BINDING_H 1

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
		class ManagementAgent;
		namespace manage {


			QPID_BROKER_CLASS_EXTERN class Binding : public ::qmf2::ManagementObject
			{
			private:

				static std::string packageName;
				static std::string className;
				static uint8_t     md5Sum[MD5_LEN];

				uint8_t presenceMask[1];
				static const uint8_t presenceByte_origin = 0;
				static const uint8_t presenceMask_origin = 1;



				// Properties
				::qmf2::ObjectId exchangeRef;
				::qmf2::ObjectId queueRef;
				std::string bindingKey;
				::qpid::types::Variant::Map arguments;
				std::string origin;

				// Statistics


				// Per-Thread Statistics

			public:
				struct PerThreadStats {
					uint64_t  msgMatched;

				};
			private:

				struct PerThreadStats** perThreadStatsArray;

				inline struct PerThreadStats* getThreadStats() {
					int idx = getThreadIndex();
					struct PerThreadStats* threadStats = perThreadStatsArray[idx];
					if (threadStats == 0) {
						threadStats = new(PerThreadStats);
						perThreadStatsArray[idx] = threadStats;
						threadStats->msgMatched = 0;

					}
					return threadStats;
				}

				void aggregatePerThreadStats(struct PerThreadStats*) const;

			public:

				typedef boost::shared_ptr<Binding> shared_ptr;


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


				QPID_BROKER_EXTERN Binding(
					::qpid::broker::ManagementAgent* agent,
					::qmf2::Manageable* coreObject, ::qmf2::Manageable* _parent, const ::qmf2::ObjectId& _queueRef, const std::string& _bindingKey, const ::qpid::types::Variant::Map& _arguments);

				QPID_BROKER_EXTERN ~Binding();

				void debugStats(const std::string& comment);



				QPID_BROKER_EXTERN static void registerSelf(
					::qpid::broker::ManagementAgent* agent);

				std::string& getPackageName() const { return packageName; }
				std::string& getClassName() const { return className; }
				uint8_t* getMd5Sum() const { return md5Sum; }

				// Method IDs

				// Accessor Methods
				inline void set_origin(const std::string& val) {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					origin = val;
					presenceMask[presenceByte_origin] |= presenceMask_origin;
					configChanged = true;
				}
				inline const std::string& get_origin() {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					return origin;
				}
				inline void clr_origin() {
					presenceMask[presenceByte_origin] &= ~presenceMask_origin;
					configChanged = true;
				}
				inline bool isSet_origin() {
					return (presenceMask[presenceByte_origin] & presenceMask_origin) != 0;
				}
				inline void inc_msgMatched(uint64_t by = 1) {
					getThreadStats()->msgMatched += by;
					instChanged = true;
				}
				inline void dec_msgMatched(uint64_t by = 1) {
					getThreadStats()->msgMatched -= by;
					instChanged = true;
				}



				struct PerThreadStats* getStatistics() { return getThreadStats(); }
				void statisticsUpdated() { instChanged = true; }

			};
		}
	}
}

#endif  /*!QPID_BROKER_MANAGE_BINDING_H*/
