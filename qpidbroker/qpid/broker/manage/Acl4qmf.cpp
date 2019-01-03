
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

#include "qmf2/Manageable.h"
#include "qmf2/Buffer.h"
#include "qpid/types/Variant.h"
#include "qpid/base/amqp0_10/Codecs.h"
#include "qpid/broker/ManagementAgent.h"
#include "qpid/broker/manage/Acl.h"
#include "qpid/broker/manage/ArgsAclLookup.h"
#include "qpid/broker/manage/ArgsAclLookupPublish.h"

#include "qpid/log/Statement.h"

#include <iostream>
#include <sstream>
#include <string.h>

namespace qpid {
	namespace broker {
		namespace manage {

			using           qpid::broker::ManagementAgent;
			using           qmf2::Manageable;
			using           qmf2::ManagementObject;
			using           qmf2::Args;
			using           qmf2::Mutex;
			using           std::string;

			string  Acl::packageName = string("org.apache.qpid.acl");
			string  Acl::className = string("acl");
			uint8_t Acl::md5Sum[MD5_LEN] =
			{ 0x4b,0xd8,0x8d,0x64,0x2f,0x35,0xd8,0x94,0x43,0x5c,0x1f,0x2e,0xe8,0xc4,0x7e,0x69 };

			Acl::Acl(ManagementAgent*, Manageable* _core, ::qmf2::Manageable* _parent) :
				ManagementObject(_core)
			{
				brokerRef = _parent->GetManagementObject()->getObjectId();
				policyFile = "";
				enforcingAcl = false;
				transferAcl = false;
				lastAclLoad = 0;
				maxConnections = 0;
				maxConnectionsPerIp = 0;
				maxConnectionsPerUser = 0;
				maxQueuesPerUser = 0;



				perThreadStatsArray = new struct PerThreadStats*[maxThreads];
				for (int idx = 0; idx < maxThreads; idx++)
					perThreadStatsArray[idx] = 0;


				QPID_LOG_CAT(trace, model, "Mgmt create " << className
					<< ". id:" << getKey());

			}

			Acl::~Acl()
			{

				for (int idx = 0; idx < maxThreads; idx++)
					if (perThreadStatsArray[idx] != 0)
						delete perThreadStatsArray[idx];
				delete[] perThreadStatsArray;

			}

			void Acl::debugStats(const std::string& comment)
			{

				bool logEnabled;
				QPID_LOG_TEST_CAT(trace, model, logEnabled);
				if (logEnabled)
				{
					::qpid::types::Variant::Map map;
					mapEncodeValues(map, false, true);
					QPID_LOG_CAT(trace, model, "Mgmt " << comment << ((comment != "") ? (" ") : ("")) << className
						<< ". id:" << getKey()
						<< " Statistics: " << map);
				}

			}


			namespace {
				const string NAME("name");
				const string TYPE("type");
				const string ACCESS("access");
				const string IS_INDEX("index");
				const string IS_OPTIONAL("optional");
				const string UNIT("unit");
				const string MIN("min");
				const string MAX("max");
				const string MAXLEN("maxlen");
				const string DESC("desc");
				const string ARGCOUNT("argCount");
				const string ARGS("args");
				const string DIR("dir");
				const string DEFAULT("default");
			}

			void Acl::registerSelf(ManagementAgent* agent)
			{
				agent->registerClass(packageName, className, md5Sum, writeSchema);
			}

			void Acl::writeSchema(std::string& schema)
			{
				const int _bufSize = 65536;
				char _msgChars[_bufSize];
				::qmf2::Buffer buf(_msgChars, _bufSize);
				::qpid::types::Variant::Map ft;

				// Schema class header:
				buf.putOctet(CLASS_KIND_TABLE);
				buf.putShortString(packageName); // Package Name
				buf.putShortString(className);   // Class Name
				buf.putBin128(md5Sum);      // Schema Hash
				buf.putShort(9); // Config Element Count
				buf.putShort(3); // Inst Element Count
				buf.putShort(3); // Method Count

				// Properties
				ft.clear();
				ft[NAME] = "brokerRef";
				ft[TYPE] = TYPE_REF;
				ft[ACCESS] = ACCESS_RO;
				ft[IS_INDEX] = 1;
				ft[IS_OPTIONAL] = 0;
				buf.putMap(ft);

				ft.clear();
				ft[NAME] = "policyFile";
				ft[TYPE] = TYPE_LSTR;
				ft[ACCESS] = ACCESS_RO;
				ft[IS_INDEX] = 0;
				ft[IS_OPTIONAL] = 0;
				ft[DESC] = "Name of the policy file";
				buf.putMap(ft);

				ft.clear();
				ft[NAME] = "enforcingAcl";
				ft[TYPE] = TYPE_BOOL;
				ft[ACCESS] = ACCESS_RO;
				ft[IS_INDEX] = 0;
				ft[IS_OPTIONAL] = 0;
				ft[DESC] = "Currently Enforcing ACL";
				buf.putMap(ft);

				ft.clear();
				ft[NAME] = "transferAcl";
				ft[TYPE] = TYPE_BOOL;
				ft[ACCESS] = ACCESS_RO;
				ft[IS_INDEX] = 0;
				ft[IS_OPTIONAL] = 0;
				ft[DESC] = "Any transfer ACL rules in force";
				buf.putMap(ft);

				ft.clear();
				ft[NAME] = "lastAclLoad";
				ft[TYPE] = TYPE_ABSTIME;
				ft[ACCESS] = ACCESS_RO;
				ft[IS_INDEX] = 0;
				ft[IS_OPTIONAL] = 0;
				ft[DESC] = "Timestamp of last successful load of ACL";
				buf.putMap(ft);

				ft.clear();
				ft[NAME] = "maxConnections";
				ft[TYPE] = TYPE_U16;
				ft[ACCESS] = ACCESS_RO;
				ft[IS_INDEX] = 0;
				ft[IS_OPTIONAL] = 0;
				ft[DESC] = "Maximum allowed connections";
				buf.putMap(ft);

				ft.clear();
				ft[NAME] = "maxConnectionsPerIp";
				ft[TYPE] = TYPE_U16;
				ft[ACCESS] = ACCESS_RO;
				ft[IS_INDEX] = 0;
				ft[IS_OPTIONAL] = 0;
				ft[DESC] = "Maximum allowed connections";
				buf.putMap(ft);

				ft.clear();
				ft[NAME] = "maxConnectionsPerUser";
				ft[TYPE] = TYPE_U16;
				ft[ACCESS] = ACCESS_RO;
				ft[IS_INDEX] = 0;
				ft[IS_OPTIONAL] = 0;
				ft[DESC] = "Maximum allowed connections";
				buf.putMap(ft);

				ft.clear();
				ft[NAME] = "maxQueuesPerUser";
				ft[TYPE] = TYPE_U16;
				ft[ACCESS] = ACCESS_RO;
				ft[IS_INDEX] = 0;
				ft[IS_OPTIONAL] = 0;
				ft[DESC] = "Maximum allowed queues";
				buf.putMap(ft);


				// Statistics
				ft.clear();
				ft[NAME] = "aclDenyCount";
				ft[TYPE] = TYPE_U64;
				ft[UNIT] = "request";
				ft[DESC] = "Number of ACL requests denied";
				buf.putMap(ft);

				ft.clear();
				ft[NAME] = "connectionDenyCount";
				ft[TYPE] = TYPE_U64;
				ft[UNIT] = "connection";
				ft[DESC] = "Number of connections denied";
				buf.putMap(ft);

				ft.clear();
				ft[NAME] = "queueQuotaDenyCount";
				ft[TYPE] = TYPE_U64;
				ft[UNIT] = "queue";
				ft[DESC] = "Number of queue creations denied";
				buf.putMap(ft);


				// Methods
				ft.clear();
				ft[NAME] = "reloadACLFile";
				ft[ARGCOUNT] = 0;
				ft[DESC] = "Reload the ACL file";
				buf.putMap(ft);

				ft.clear();
				ft[NAME] = "Lookup";
				ft[ARGCOUNT] = 6;
				ft[DESC] = "Lookup: user action object [objectName [propertyMap]]";
				buf.putMap(ft);

				ft.clear();
				ft[NAME] = "userId";
				ft[TYPE] = TYPE_LSTR;
				ft[DIR] = "I";
				buf.putMap(ft);

				ft.clear();
				ft[NAME] = "action";
				ft[TYPE] = TYPE_LSTR;
				ft[DIR] = "I";
				buf.putMap(ft);

				ft.clear();
				ft[NAME] = "object";
				ft[TYPE] = TYPE_LSTR;
				ft[DIR] = "I";
				buf.putMap(ft);

				ft.clear();
				ft[NAME] = "objectName";
				ft[TYPE] = TYPE_LSTR;
				ft[DIR] = "I";
				buf.putMap(ft);

				ft.clear();
				ft[NAME] = "propertyMap";
				ft[TYPE] = TYPE_FTABLE;
				ft[DIR] = "I";
				buf.putMap(ft);

				ft.clear();
				ft[NAME] = "result";
				ft[TYPE] = TYPE_LSTR;
				ft[DIR] = "O";
				buf.putMap(ft);

				ft.clear();
				ft[NAME] = "LookupPublish";
				ft[ARGCOUNT] = 4;
				ft[DESC] = "Lookup PUBLISH EXCHANGE: user exchangeName routingKey";
				buf.putMap(ft);

				ft.clear();
				ft[NAME] = "userId";
				ft[TYPE] = TYPE_LSTR;
				ft[DIR] = "I";
				buf.putMap(ft);

				ft.clear();
				ft[NAME] = "exchangeName";
				ft[TYPE] = TYPE_LSTR;
				ft[DIR] = "I";
				buf.putMap(ft);

				ft.clear();
				ft[NAME] = "routingKey";
				ft[TYPE] = TYPE_LSTR;
				ft[DIR] = "I";
				buf.putMap(ft);

				ft.clear();
				ft[NAME] = "result";
				ft[TYPE] = TYPE_LSTR;
				ft[DIR] = "O";
				buf.putMap(ft);


				{
					uint32_t _len = buf.getPosition();
					buf.reset();
					buf.getRawData(schema, _len);
				}
			}


			void Acl::aggregatePerThreadStats(struct PerThreadStats* totals) const
			{
				totals->aclDenyCount = 0;
				totals->connectionDenyCount = 0;
				totals->queueQuotaDenyCount = 0;

				for (int idx = 0; idx < maxThreads; idx++) {
					struct PerThreadStats* threadStats = perThreadStatsArray[idx];
					if (threadStats != 0) {
						totals->aclDenyCount += threadStats->aclDenyCount;
						totals->connectionDenyCount += threadStats->connectionDenyCount;
						totals->queueQuotaDenyCount += threadStats->queueQuotaDenyCount;

					}
				}
			}



			uint32_t Acl::writePropertiesSize() const
			{
				uint32_t size = writeTimestampsSize();

				size += 16;  // brokerRef
				size += (2 + policyFile.length());  // policyFile
				size += 1;  // enforcingAcl
				size += 1;  // transferAcl
				size += 8;  // lastAclLoad
				size += 2;  // maxConnections
				size += 2;  // maxConnectionsPerIp
				size += 2;  // maxConnectionsPerUser
				size += 2;  // maxQueuesPerUser

				return size;
			}

			void Acl::readProperties(const std::string& _sBuf)
			{
				char *_tmpBuf = new char[_sBuf.length()];
				memcpy(_tmpBuf, _sBuf.data(), _sBuf.length());
				::qmf2::Buffer buf(_tmpBuf, _sBuf.length());
				Mutex::ScopedLock mutex(accessLock);

				{
					std::string _tbuf;
					buf.getRawData(_tbuf, writeTimestampsSize());
					readTimestamps(_tbuf);
				}


				{std::string _s; buf.getRawData(_s, brokerRef.encodedSize()); brokerRef.decode(_s); };
				buf.getMediumString(policyFile);
				enforcingAcl = buf.getOctet() == 1;
				transferAcl = buf.getOctet() == 1;
				lastAclLoad = buf.getLongLong();
				maxConnections = buf.getShort();
				maxConnectionsPerIp = buf.getShort();
				maxConnectionsPerUser = buf.getShort();
				maxQueuesPerUser = buf.getShort();


				delete[] _tmpBuf;
			}

			void Acl::writeProperties(std::string& _sBuf) const
			{
				const int _bufSize = 65536;
				char _msgChars[_bufSize];
				::qmf2::Buffer buf(_msgChars, _bufSize);

				Mutex::ScopedLock mutex(accessLock);
				configChanged = false;

				{
					std::string _tbuf;
					writeTimestamps(_tbuf);
					buf.putRawData(_tbuf);
				}



				{std::string _s; brokerRef.encode(_s); buf.putRawData(_s); };
				buf.putMediumString(policyFile);
				buf.putOctet(enforcingAcl ? 1 : 0);
				buf.putOctet(transferAcl ? 1 : 0);
				buf.putLongLong(lastAclLoad);
				buf.putShort(maxConnections);
				buf.putShort(maxConnectionsPerIp);
				buf.putShort(maxConnectionsPerUser);
				buf.putShort(maxQueuesPerUser);


				uint32_t _bufLen = buf.getPosition();
				buf.reset();

				buf.getRawData(_sBuf, _bufLen);
			}

			void Acl::writeStatistics(std::string& _sBuf, bool skipHeaders)
			{
				const int _bufSize = 65536;
				char _msgChars[_bufSize];
				::qmf2::Buffer buf(_msgChars, _bufSize);

				Mutex::ScopedLock mutex(accessLock);
				instChanged = false;


				struct PerThreadStats totals;
				aggregatePerThreadStats(&totals);


				if (!skipHeaders) {
					std::string _tbuf;
					writeTimestamps(_tbuf);
					buf.putRawData(_tbuf);
				}

				buf.putLongLong(totals.aclDenyCount);
				buf.putLongLong(totals.connectionDenyCount);
				buf.putLongLong(totals.queueQuotaDenyCount);


				// Maintenance of hi-lo statistics



				uint32_t _bufLen = buf.getPosition();
				buf.reset();

				buf.getRawData(_sBuf, _bufLen);
			}

			void Acl::doMethod(string& methodName, const string& inStr, string& outStr, const string& userId)
			{
				Manageable::status_t status = Manageable::STATUS_UNKNOWN_METHOD;
				std::string          text;

				bool _matched = false;

				const int _bufSize = 65536;
				char _msgChars[_bufSize];
				::qmf2::Buffer outBuf(_msgChars, _bufSize);


				char *_tmpBuf = new char[inStr.length()];
				memcpy(_tmpBuf, inStr.data(), inStr.length());
				::qmf2::Buffer inBuf(_tmpBuf, inStr.length());

				if (methodName == "reloadACLFile") {
					_matched = true;
					::qmf2::ArgsNone ioArgs;
					bool allow = manageable.AuthorizeMethod(METHOD_RELOADACLFILE, ioArgs, userId);
					if (allow)
						status = manageable.ManagementMethod(METHOD_RELOADACLFILE, ioArgs, text);
					else
						status = Manageable::STATUS_FORBIDDEN;
					outBuf.putLong(status);
					outBuf.putMediumString(::qmf2::Manageable::StatusText(status, text));
				}

				if (methodName == "Lookup") {
					_matched = true;
					ArgsAclLookup ioArgs;
					inBuf.getMediumString(ioArgs.i_userId);
					inBuf.getMediumString(ioArgs.i_action);
					inBuf.getMediumString(ioArgs.i_object);
					inBuf.getMediumString(ioArgs.i_objectName);
					inBuf.getMap(ioArgs.i_propertyMap);
					bool allow = manageable.AuthorizeMethod(METHOD_LOOKUP, ioArgs, userId);
					if (allow)
						status = manageable.ManagementMethod(METHOD_LOOKUP, ioArgs, text);
					else
						status = Manageable::STATUS_FORBIDDEN;
					outBuf.putLong(status);
					outBuf.putMediumString(::qmf2::Manageable::StatusText(status, text));
					outBuf.putMediumString(ioArgs.o_result);
				}

				if (methodName == "LookupPublish") {
					_matched = true;
					ArgsAclLookupPublish ioArgs;
					inBuf.getMediumString(ioArgs.i_userId);
					inBuf.getMediumString(ioArgs.i_exchangeName);
					inBuf.getMediumString(ioArgs.i_routingKey);
					bool allow = manageable.AuthorizeMethod(METHOD_LOOKUPPUBLISH, ioArgs, userId);
					if (allow)
						status = manageable.ManagementMethod(METHOD_LOOKUPPUBLISH, ioArgs, text);
					else
						status = Manageable::STATUS_FORBIDDEN;
					outBuf.putLong(status);
					outBuf.putMediumString(::qmf2::Manageable::StatusText(status, text));
					outBuf.putMediumString(ioArgs.o_result);
				}

				delete[] _tmpBuf;


				if (!_matched) {
					outBuf.putLong(status);
					outBuf.putShortString(Manageable::StatusText(status, text));
				}

				uint32_t _bufLen = outBuf.getPosition();
				outBuf.reset();

				outBuf.getRawData(outStr, _bufLen);
			}

			std::string Acl::getKey() const
			{
				std::stringstream key;

				key << brokerRef.getV2Key();
				return key.str();
			}


			void Acl::mapEncodeValues(::qpid::types::Variant::Map& _map,
				bool includeProperties,
				bool includeStatistics)
			{
				using namespace ::qpid::types;
				Mutex::ScopedLock mutex(accessLock);

				if (includeProperties) {
					configChanged = false;
					_map["brokerRef"] = ::qpid::types::Variant(brokerRef);
					_map["policyFile"] = ::qpid::types::Variant(policyFile);
					_map["enforcingAcl"] = ::qpid::types::Variant(enforcingAcl);
					_map["transferAcl"] = ::qpid::types::Variant(transferAcl);
					_map["lastAclLoad"] = ::qpid::types::Variant(lastAclLoad);
					_map["maxConnections"] = ::qpid::types::Variant(maxConnections);
					_map["maxConnectionsPerIp"] = ::qpid::types::Variant(maxConnectionsPerIp);
					_map["maxConnectionsPerUser"] = ::qpid::types::Variant(maxConnectionsPerUser);
					_map["maxQueuesPerUser"] = ::qpid::types::Variant(maxQueuesPerUser);

				}

				if (includeStatistics) {
					instChanged = false;


					struct PerThreadStats totals;
					aggregatePerThreadStats(&totals);



					_map["aclDenyCount"] = ::qpid::types::Variant(totals.aclDenyCount);
					_map["connectionDenyCount"] = ::qpid::types::Variant(totals.connectionDenyCount);
					_map["queueQuotaDenyCount"] = ::qpid::types::Variant(totals.queueQuotaDenyCount);


					// Maintenance of hi-lo statistics


				}
			}

			void Acl::mapDecodeValues(const ::qpid::types::Variant::Map& _map)
			{
				::qpid::types::Variant::Map::const_iterator _i;
				Mutex::ScopedLock mutex(accessLock);

				if ((_i = _map.find("brokerRef")) != _map.end()) {
					brokerRef = _i->second;
				}
				else {
					brokerRef = ::qmf2::ObjectId();
				}
				if ((_i = _map.find("policyFile")) != _map.end()) {
					policyFile = (_i->second).getString();
				}
				else {
					policyFile = "";
				}
				if ((_i = _map.find("enforcingAcl")) != _map.end()) {
					enforcingAcl = _i->second;
				}
				else {
					enforcingAcl = false;
				}
				if ((_i = _map.find("transferAcl")) != _map.end()) {
					transferAcl = _i->second;
				}
				else {
					transferAcl = false;
				}
				if ((_i = _map.find("lastAclLoad")) != _map.end()) {
					lastAclLoad = _i->second;
				}
				else {
					lastAclLoad = 0;
				}
				if ((_i = _map.find("maxConnections")) != _map.end()) {
					maxConnections = _i->second;
				}
				else {
					maxConnections = 0;
				}
				if ((_i = _map.find("maxConnectionsPerIp")) != _map.end()) {
					maxConnectionsPerIp = _i->second;
				}
				else {
					maxConnectionsPerIp = 0;
				}
				if ((_i = _map.find("maxConnectionsPerUser")) != _map.end()) {
					maxConnectionsPerUser = _i->second;
				}
				else {
					maxConnectionsPerUser = 0;
				}
				if ((_i = _map.find("maxQueuesPerUser")) != _map.end()) {
					maxQueuesPerUser = _i->second;
				}
				else {
					maxQueuesPerUser = 0;
				}

			}

			void Acl::doMethod(string& methodName, const ::qpid::types::Variant::Map& inMap, ::qpid::types::Variant::Map& outMap, const string& userId)
			{
				Manageable::status_t status = Manageable::STATUS_UNKNOWN_METHOD;
				std::string          text;


				if (methodName == "reloadACLFile") {
					::qmf2::ArgsNone ioArgs;
					bool allow = manageable.AuthorizeMethod(METHOD_RELOADACLFILE, ioArgs, userId);
					if (allow)
						status = manageable.ManagementMethod(METHOD_RELOADACLFILE, ioArgs, text);
					else
						status = Manageable::STATUS_FORBIDDEN;
					outMap["_status_code"] = (uint32_t)status;
					outMap["_status_text"] = ::qmf2::Manageable::StatusText(status, text);
					return;
				}

				if (methodName == "Lookup") {
					ArgsAclLookup ioArgs;
					::qpid::types::Variant::Map::const_iterator _i;
					if ((_i = inMap.find("userId")) != inMap.end()) {
						ioArgs.i_userId = (_i->second).getString();
					}
					else {
						ioArgs.i_userId = "";
					}
					if ((_i = inMap.find("action")) != inMap.end()) {
						ioArgs.i_action = (_i->second).getString();
					}
					else {
						ioArgs.i_action = "";
					}
					if ((_i = inMap.find("object")) != inMap.end()) {
						ioArgs.i_object = (_i->second).getString();
					}
					else {
						ioArgs.i_object = "";
					}
					if ((_i = inMap.find("objectName")) != inMap.end()) {
						ioArgs.i_objectName = (_i->second).getString();
					}
					else {
						ioArgs.i_objectName = "";
					}
					if ((_i = inMap.find("propertyMap")) != inMap.end()) {
						ioArgs.i_propertyMap = (_i->second).asMap();
					}
					else {
						ioArgs.i_propertyMap = ::qpid::types::Variant::Map();
					}
					bool allow = manageable.AuthorizeMethod(METHOD_LOOKUP, ioArgs, userId);
					if (allow)
						status = manageable.ManagementMethod(METHOD_LOOKUP, ioArgs, text);
					else
						status = Manageable::STATUS_FORBIDDEN;
					outMap["_status_code"] = (uint32_t)status;
					outMap["_status_text"] = ::qmf2::Manageable::StatusText(status, text);
					outMap["result"] = ::qpid::types::Variant(ioArgs.o_result);
					return;
				}

				if (methodName == "LookupPublish") {
					ArgsAclLookupPublish ioArgs;
					::qpid::types::Variant::Map::const_iterator _i;
					if ((_i = inMap.find("userId")) != inMap.end()) {
						ioArgs.i_userId = (_i->second).getString();
					}
					else {
						ioArgs.i_userId = "";
					}
					if ((_i = inMap.find("exchangeName")) != inMap.end()) {
						ioArgs.i_exchangeName = (_i->second).getString();
					}
					else {
						ioArgs.i_exchangeName = "";
					}
					if ((_i = inMap.find("routingKey")) != inMap.end()) {
						ioArgs.i_routingKey = (_i->second).getString();
					}
					else {
						ioArgs.i_routingKey = "";
					}
					bool allow = manageable.AuthorizeMethod(METHOD_LOOKUPPUBLISH, ioArgs, userId);
					if (allow)
						status = manageable.ManagementMethod(METHOD_LOOKUPPUBLISH, ioArgs, text);
					else
						status = Manageable::STATUS_FORBIDDEN;
					outMap["_status_code"] = (uint32_t)status;
					outMap["_status_text"] = ::qmf2::Manageable::StatusText(status, text);
					outMap["result"] = ::qpid::types::Variant(ioArgs.o_result);
					return;
				}

				outMap["_status_code"] = (uint32_t)status;
				outMap["_status_text"] = Manageable::StatusText(status, text);
			}
		}
	}
}
