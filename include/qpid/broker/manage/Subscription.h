
#ifndef QPID_BROKER_MANAGE_SUBSCRIPTION_H
#define QPID_BROKER_MANAGE_SUBSCRIPTION_H 1

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


			QPID_BROKER_CLASS_EXTERN class Subscription : public ::qmf2::ManagementObject
			{
			private:

				static std::string packageName;
				static std::string className;
				static uint8_t     md5Sum[MD5_LEN];


				// Properties
				::qmf2::ObjectId sessionRef;
				::qmf2::ObjectId queueRef;
				std::string name;
				bool browsing;
				bool acknowledged;
				bool exclusive;
				std::string creditMode;
				::qpid::types::Variant::Map arguments;

				// Statistics


				// Per-Thread Statistics

			public:
				struct PerThreadStats {
					uint64_t  delivered;

				};
			private:

				struct PerThreadStats** perThreadStatsArray;

				inline struct PerThreadStats* getThreadStats() {
					int idx = getThreadIndex();
					struct PerThreadStats* threadStats = perThreadStatsArray[idx];
					if (threadStats == 0) {
						threadStats = new(PerThreadStats);
						perThreadStatsArray[idx] = threadStats;
						threadStats->delivered = 0;

					}
					return threadStats;
				}

				void aggregatePerThreadStats(struct PerThreadStats*) const;

			public:

				typedef boost::shared_ptr<Subscription> shared_ptr;


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


				QPID_BROKER_EXTERN Subscription(
					::qpid::broker::ManagementAgent* agent,
					::qmf2::Manageable* coreObject, ::qmf2::Manageable* _parent, const ::qmf2::ObjectId& _queueRef, const std::string& _name, bool _browsing, bool _acknowledged, bool _exclusive, const ::qpid::types::Variant::Map& _arguments);

				QPID_BROKER_EXTERN ~Subscription();

				void debugStats(const std::string& comment);



				QPID_BROKER_EXTERN static void registerSelf(
					::qpid::broker::ManagementAgent* agent);

				std::string& getPackageName() const { return packageName; }
				std::string& getClassName() const { return className; }
				uint8_t* getMd5Sum() const { return md5Sum; }

				// Method IDs

				// Accessor Methods
				inline void set_creditMode(const std::string& val) {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					creditMode = val;
					configChanged = true;
				}
				inline const std::string& get_creditMode() {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					return creditMode;
				}
				inline void inc_delivered(uint64_t by = 1) {
					getThreadStats()->delivered += by;
					instChanged = true;
				}
				inline void dec_delivered(uint64_t by = 1) {
					getThreadStats()->delivered -= by;
					instChanged = true;
				}



				struct PerThreadStats* getStatistics() { return getThreadStats(); }
				void statisticsUpdated() { instChanged = true; }

			};

		}
	}
}

#endif  /*!QPID_BROKER_MANAGE_SUBSCRIPTION_H*/
