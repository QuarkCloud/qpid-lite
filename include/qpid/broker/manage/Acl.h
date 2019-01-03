
#ifndef QPID_BROKER_MANAGE_ACL_H
#define QPID_BROKER_MANAGE_ACL_H 1

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


			QPID_BROKER_CLASS_EXTERN class Acl : public ::qmf2::ManagementObject
			{
			private:

				static std::string packageName;
				static std::string className;
				static uint8_t     md5Sum[MD5_LEN];


				// Properties
				::qmf2::ObjectId brokerRef;
				std::string policyFile;
				bool enforcingAcl;
				bool transferAcl;
				int64_t lastAclLoad;
				uint16_t maxConnections;
				uint16_t maxConnectionsPerIp;
				uint16_t maxConnectionsPerUser;
				uint16_t maxQueuesPerUser;

				// Statistics


				// Per-Thread Statistics

			public:
				struct PerThreadStats {
					uint64_t  aclDenyCount;
					uint64_t  connectionDenyCount;
					uint64_t  queueQuotaDenyCount;

				};
			private:

				struct PerThreadStats** perThreadStatsArray;

				inline struct PerThreadStats* getThreadStats() {
					int idx = getThreadIndex();
					struct PerThreadStats* threadStats = perThreadStatsArray[idx];
					if (threadStats == 0) {
						threadStats = new(PerThreadStats);
						perThreadStatsArray[idx] = threadStats;
						threadStats->aclDenyCount = 0;
						threadStats->connectionDenyCount = 0;
						threadStats->queueQuotaDenyCount = 0;

					}
					return threadStats;
				}

				void aggregatePerThreadStats(struct PerThreadStats*) const;

			public:

				typedef boost::shared_ptr<Acl> shared_ptr;


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


				QPID_BROKER_EXTERN Acl(
					::qpid::broker::ManagementAgent* agent,
					::qmf2::Manageable* coreObject, ::qmf2::Manageable* _parent);

				QPID_BROKER_EXTERN ~Acl();

				void debugStats(const std::string& comment);



				QPID_BROKER_EXTERN static void registerSelf(
					::qpid::broker::ManagementAgent* agent);

				std::string& getPackageName() const { return packageName; }
				std::string& getClassName() const { return className; }
				uint8_t* getMd5Sum() const { return md5Sum; }

				// Method IDs
				QPID_BROKER_EXTERN static const uint32_t METHOD_RELOADACLFILE = 1;
				QPID_BROKER_EXTERN static const uint32_t METHOD_LOOKUP = 2;
				QPID_BROKER_EXTERN static const uint32_t METHOD_LOOKUPPUBLISH = 3;

				// Accessor Methods
				inline void set_brokerRef(const ::qmf2::ObjectId& val) {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					brokerRef = val;
					configChanged = true;
				}
				inline const ::qmf2::ObjectId& get_brokerRef() {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					return brokerRef;
				}
				inline void set_policyFile(const std::string& val) {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					policyFile = val;
					configChanged = true;
				}
				inline const std::string& get_policyFile() {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					return policyFile;
				}
				inline void set_enforcingAcl(bool val) {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					enforcingAcl = val;
					configChanged = true;
				}
				inline bool get_enforcingAcl() {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					return enforcingAcl;
				}
				inline void set_transferAcl(bool val) {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					transferAcl = val;
					configChanged = true;
				}
				inline bool get_transferAcl() {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					return transferAcl;
				}
				inline void set_lastAclLoad(int64_t val) {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					lastAclLoad = val;
					configChanged = true;
				}
				inline int64_t get_lastAclLoad() {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					return lastAclLoad;
				}
				inline void set_maxConnections(uint16_t val) {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					maxConnections = val;
					configChanged = true;
				}
				inline uint16_t get_maxConnections() {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					return maxConnections;
				}
				inline void set_maxConnectionsPerIp(uint16_t val) {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					maxConnectionsPerIp = val;
					configChanged = true;
				}
				inline uint16_t get_maxConnectionsPerIp() {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					return maxConnectionsPerIp;
				}
				inline void set_maxConnectionsPerUser(uint16_t val) {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					maxConnectionsPerUser = val;
					configChanged = true;
				}
				inline uint16_t get_maxConnectionsPerUser() {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					return maxConnectionsPerUser;
				}
				inline void set_maxQueuesPerUser(uint16_t val) {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					maxQueuesPerUser = val;
					configChanged = true;
				}
				inline uint16_t get_maxQueuesPerUser() {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					return maxQueuesPerUser;
				}
				inline void inc_aclDenyCount(uint64_t by = 1) {
					getThreadStats()->aclDenyCount += by;
					instChanged = true;
				}
				inline void dec_aclDenyCount(uint64_t by = 1) {
					getThreadStats()->aclDenyCount -= by;
					instChanged = true;
				}
				inline void inc_connectionDenyCount(uint64_t by = 1) {
					getThreadStats()->connectionDenyCount += by;
					instChanged = true;
				}
				inline void dec_connectionDenyCount(uint64_t by = 1) {
					getThreadStats()->connectionDenyCount -= by;
					instChanged = true;
				}
				inline void inc_queueQuotaDenyCount(uint64_t by = 1) {
					getThreadStats()->queueQuotaDenyCount += by;
					instChanged = true;
				}
				inline void dec_queueQuotaDenyCount(uint64_t by = 1) {
					getThreadStats()->queueQuotaDenyCount -= by;
					instChanged = true;
				}



				struct PerThreadStats* getStatistics() { return getThreadStats(); }
				void statisticsUpdated() { instChanged = true; }

			};
		}
	}
}

#endif  /*!QPID_BROKER_MANAGE_ACL_H*/
