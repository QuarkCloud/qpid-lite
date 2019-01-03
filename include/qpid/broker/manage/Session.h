
#ifndef QPID_BROKER_MANAGE_SESSION_H
#define QPID_BROKER_MANAGE_SESSION_H 1

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


			QPID_BROKER_CLASS_EXTERN class Session : public ::qmf2::ManagementObject
			{
			private:

				static std::string packageName;
				static std::string className;
				static uint8_t     md5Sum[MD5_LEN];

				uint8_t presenceMask[1];
				static const uint8_t presenceByte_fullName = 0;
				static const uint8_t presenceMask_fullName = 1;
				static const uint8_t presenceByte_expireTime = 0;
				static const uint8_t presenceMask_expireTime = 2;
				static const uint8_t presenceByte_maxClientRate = 0;
				static const uint8_t presenceMask_maxClientRate = 4;



				// Properties
				::qmf2::ObjectId vhostRef;
				std::string name;
				std::string fullName;
				uint16_t channelId;
				::qmf2::ObjectId connectionRef;
				uint32_t detachedLifespan;
				bool attached;
				int64_t expireTime;
				uint32_t maxClientRate;

				// Statistics
				uint64_t  unackedMessages;


				// Per-Thread Statistics

			public:
				struct PerThreadStats {
					uint64_t  TxnStarts;
					uint64_t  TxnCommits;
					uint64_t  TxnRejects;
					uint32_t  TxnCount;
					uint32_t  clientCredit;
					uint32_t  framesOutstanding;

				};
			private:

				struct PerThreadStats** perThreadStatsArray;

				inline struct PerThreadStats* getThreadStats() {
					int idx = getThreadIndex();
					struct PerThreadStats* threadStats = perThreadStatsArray[idx];
					if (threadStats == 0) {
						threadStats = new(PerThreadStats);
						perThreadStatsArray[idx] = threadStats;
						threadStats->TxnStarts = 0;
						threadStats->TxnCommits = 0;
						threadStats->TxnRejects = 0;
						threadStats->TxnCount = 0;
						threadStats->clientCredit = 0;
						threadStats->framesOutstanding = 0;

					}
					return threadStats;
				}

				void aggregatePerThreadStats(struct PerThreadStats*) const;

			public:

				typedef boost::shared_ptr<Session> shared_ptr;


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


				QPID_BROKER_EXTERN Session(
					::qpid::broker::ManagementAgent* agent,
					::qmf2::Manageable* coreObject, ::qmf2::Manageable* _parent, const std::string& _name);

				QPID_BROKER_EXTERN ~Session();

				void debugStats(const std::string& comment);



				QPID_BROKER_EXTERN static void registerSelf(
					::qpid::broker::ManagementAgent* agent);

				std::string& getPackageName() const { return packageName; }
				std::string& getClassName() const { return className; }
				uint8_t* getMd5Sum() const { return md5Sum; }

				// Method IDs
				QPID_BROKER_EXTERN static const uint32_t METHOD_SOLICITACK = 1;
				QPID_BROKER_EXTERN static const uint32_t METHOD_DETACH = 2;
				QPID_BROKER_EXTERN static const uint32_t METHOD_RESETLIFESPAN = 3;
				QPID_BROKER_EXTERN static const uint32_t METHOD_CLOSE = 4;

				// Accessor Methods
				inline void set_fullName(const std::string& val) {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					fullName = val;
					presenceMask[presenceByte_fullName] |= presenceMask_fullName;
					configChanged = true;
				}
				inline const std::string& get_fullName() {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					return fullName;
				}
				inline void clr_fullName() {
					presenceMask[presenceByte_fullName] &= ~presenceMask_fullName;
					configChanged = true;
				}
				inline bool isSet_fullName() {
					return (presenceMask[presenceByte_fullName] & presenceMask_fullName) != 0;
				}
				inline void set_channelId(uint16_t val) {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					channelId = val;
					configChanged = true;
				}
				inline uint16_t get_channelId() {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					return channelId;
				}
				inline void set_connectionRef(const ::qmf2::ObjectId& val) {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					connectionRef = val;
					configChanged = true;
				}
				inline const ::qmf2::ObjectId& get_connectionRef() {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					return connectionRef;
				}
				inline void set_detachedLifespan(uint32_t val) {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					detachedLifespan = val;
					configChanged = true;
				}
				inline uint32_t get_detachedLifespan() {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					return detachedLifespan;
				}
				inline void set_attached(bool val) {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					attached = val;
					configChanged = true;
				}
				inline bool get_attached() {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					return attached;
				}
				inline void set_expireTime(int64_t val) {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					expireTime = val;
					presenceMask[presenceByte_expireTime] |= presenceMask_expireTime;
					configChanged = true;
				}
				inline int64_t get_expireTime() {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					return expireTime;
				}
				inline void clr_expireTime() {
					presenceMask[presenceByte_expireTime] &= ~presenceMask_expireTime;
					configChanged = true;
				}
				inline bool isSet_expireTime() {
					return (presenceMask[presenceByte_expireTime] & presenceMask_expireTime) != 0;
				}
				inline void set_maxClientRate(uint32_t val) {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					maxClientRate = val;
					presenceMask[presenceByte_maxClientRate] |= presenceMask_maxClientRate;
					configChanged = true;
				}
				inline uint32_t get_maxClientRate() {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					return maxClientRate;
				}
				inline void clr_maxClientRate() {
					presenceMask[presenceByte_maxClientRate] &= ~presenceMask_maxClientRate;
					configChanged = true;
				}
				inline bool isSet_maxClientRate() {
					return (presenceMask[presenceByte_maxClientRate] & presenceMask_maxClientRate) != 0;
				}
				inline void set_unackedMessages(uint64_t val) {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					unackedMessages = val;
					instChanged = true;
				}
				inline uint64_t get_unackedMessages() {
					::qmf2::Mutex::ScopedLock mutex(accessLock);
					return unackedMessages;
				}
				inline void inc_TxnStarts(uint64_t by = 1) {
					getThreadStats()->TxnStarts += by;
					instChanged = true;
				}
				inline void dec_TxnStarts(uint64_t by = 1) {
					getThreadStats()->TxnStarts -= by;
					instChanged = true;
				}
				inline void inc_TxnCommits(uint64_t by = 1) {
					getThreadStats()->TxnCommits += by;
					instChanged = true;
				}
				inline void dec_TxnCommits(uint64_t by = 1) {
					getThreadStats()->TxnCommits -= by;
					instChanged = true;
				}
				inline void inc_TxnRejects(uint64_t by = 1) {
					getThreadStats()->TxnRejects += by;
					instChanged = true;
				}
				inline void dec_TxnRejects(uint64_t by = 1) {
					getThreadStats()->TxnRejects -= by;
					instChanged = true;
				}
				inline void inc_TxnCount(uint32_t by = 1) {
					getThreadStats()->TxnCount += by;
					instChanged = true;
				}
				inline void dec_TxnCount(uint32_t by = 1) {
					getThreadStats()->TxnCount -= by;
					instChanged = true;
				}
				inline void inc_clientCredit(uint32_t by = 1) {
					getThreadStats()->clientCredit += by;
					instChanged = true;
				}
				inline void dec_clientCredit(uint32_t by = 1) {
					getThreadStats()->clientCredit -= by;
					instChanged = true;
				}
				inline void inc_framesOutstanding(uint32_t by = 1) {
					getThreadStats()->framesOutstanding += by;
					instChanged = true;
				}
				inline void dec_framesOutstanding(uint32_t by = 1) {
					getThreadStats()->framesOutstanding -= by;
					instChanged = true;
				}



				struct PerThreadStats* getStatistics() { return getThreadStats(); }
				void statisticsUpdated() { instChanged = true; }

			};
		}
	}
}

#endif  /*!QPID_BROKER_MANAGE_SESSION_H*/
