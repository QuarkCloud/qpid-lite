
#ifndef QPID_BROKER_MANAGE_OUTGOING_H
#define QPID_BROKER_MANAGE_OUTGOING_H 1

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


			QPID_BROKER_CLASS_EXTERN class Outgoing : public ::qmf2::ManagementObject
			{
			private:

				static std::string packageName;
				static std::string className;
				static uint8_t     md5Sum[MD5_LEN];


				// Properties
				::qmf2::ObjectId sessionRef;
				std::string containerid;
				std::string name;
				std::string source;
				std::string target;
				std::string domain;

				// Statistics


				// Per-Thread Statistics

			public:
				struct PerThreadStats {
					uint64_t  transfers;

				};
			private:

				struct PerThreadStats** perThreadStatsArray;

				inline struct PerThreadStats* getThreadStats() {
					int idx = getThreadIndex();
					struct PerThreadStats* threadStats = perThreadStatsArray[idx];
					if (threadStats == 0) {
						threadStats = new(PerThreadStats);
						perThreadStatsArray[idx] = threadStats;
						threadStats->transfers = 0;

					}
					return threadStats;
				}

				void aggregatePerThreadStats(struct PerThreadStats*) const;

			public:

				typedef boost::shared_ptr<Outgoing> shared_ptr;


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


				QPID_BROKER_EXTERN Outgoing(
					::qpid::broker::ManagementAgent* agent,
					::qmf2::Manageable* coreObject, ::qmf2::Manageable* _parent, const std::string& _containerid, const std::string& _name, const std::string& _source, const std::string& _target, const std::string& _domain);

				QPID_BROKER_EXTERN ~Outgoing();

				void debugStats(const std::string& comment);



				QPID_BROKER_EXTERN static void registerSelf(
					::qpid::broker::ManagementAgent* agent);

				std::string& getPackageName() const { return packageName; }
				std::string& getClassName() const { return className; }
				uint8_t* getMd5Sum() const { return md5Sum; }

				// Method IDs

				// Accessor Methods
				inline void inc_transfers(uint64_t by = 1) {
					getThreadStats()->transfers += by;
					instChanged = true;
				}
				inline void dec_transfers(uint64_t by = 1) {
					getThreadStats()->transfers -= by;
					instChanged = true;
				}



				struct PerThreadStats* getStatistics() { return getThreadStats(); }
				void statisticsUpdated() { instChanged = true; }

			};
		}
	}
}

#endif  /*!QPID_BROKER_MANAGE_OUTGOING_H*/
