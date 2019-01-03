
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
#include "qpid/broker/amqp0_10/Codecs.h"
#include "qpid/broker/ManagementAgent.h"
#include "qpid/broker/manage/Domain.h"


#include "qpid/log/Statement.h"

#include <iostream>
#include <sstream>
#include <string.h>

namespace qpid {
	namespace broker {
		namespace manage {

			using           qmf2::Manageable;
			using           qmf2::ManagementObject;
			using           qmf2::Args;
			using           qmf2::Mutex;
			using           std::string;

			string  Domain::packageName = string("org.apache.qpid.broker");
			string  Domain::className = string("domain");
			uint8_t Domain::md5Sum[MD5_LEN] =
			{ 0xdd,0x2e,0x72,0xca,0x9,0xd2,0x64,0xc6,0xff,0x47,0x38,0xa2,0x9b,0x5e,0xbe,0xe4 };

			Domain::Domain(ManagementAgent*, Manageable* _core, const std::string& _name, bool _durable) :
				ManagementObject(_core), name(_name), durable(_durable)
			{

				url = "";
				mechanisms = "";
				username = "";
				password = "";




				QPID_LOG_CAT(trace, model, "Mgmt create " << className
					<< ". id:" << getKey());

			}

			Domain::~Domain()
			{

			}

			void Domain::debugStats(const std::string& comment)
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

			void Domain::registerSelf(ManagementAgent* agent)
			{
				agent->registerClass(packageName, className, md5Sum, writeSchema);
			}

			void Domain::writeSchema(std::string& schema)
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
				buf.putShort(6); // Config Element Count
				buf.putShort(0); // Inst Element Count
				buf.putShort(0); // Method Count

				// Properties
				ft.clear();
				ft[NAME] = "name";
				ft[TYPE] = TYPE_SSTR;
				ft[ACCESS] = ACCESS_RC;
				ft[IS_INDEX] = 1;
				ft[IS_OPTIONAL] = 0;
				buf.putMap(ft);

				ft.clear();
				ft[NAME] = "durable";
				ft[TYPE] = TYPE_BOOL;
				ft[ACCESS] = ACCESS_RC;
				ft[IS_INDEX] = 0;
				ft[IS_OPTIONAL] = 0;
				buf.putMap(ft);

				ft.clear();
				ft[NAME] = "url";
				ft[TYPE] = TYPE_SSTR;
				ft[ACCESS] = ACCESS_RO;
				ft[IS_INDEX] = 0;
				ft[IS_OPTIONAL] = 0;
				buf.putMap(ft);

				ft.clear();
				ft[NAME] = "mechanisms";
				ft[TYPE] = TYPE_SSTR;
				ft[ACCESS] = ACCESS_RO;
				ft[IS_INDEX] = 0;
				ft[IS_OPTIONAL] = 0;
				buf.putMap(ft);

				ft.clear();
				ft[NAME] = "username";
				ft[TYPE] = TYPE_SSTR;
				ft[ACCESS] = ACCESS_RO;
				ft[IS_INDEX] = 0;
				ft[IS_OPTIONAL] = 0;
				buf.putMap(ft);

				ft.clear();
				ft[NAME] = "password";
				ft[TYPE] = TYPE_SSTR;
				ft[ACCESS] = ACCESS_RO;
				ft[IS_INDEX] = 0;
				ft[IS_OPTIONAL] = 0;
				buf.putMap(ft);


				// Statistics

				// Methods

				{
					uint32_t _len = buf.getPosition();
					buf.reset();
					buf.getRawData(schema, _len);
				}
			}




			uint32_t Domain::writePropertiesSize() const
			{
				uint32_t size = writeTimestampsSize();

				size += (1 + name.length());  // name
				size += 1;  // durable
				size += (1 + url.length());  // url
				size += (1 + mechanisms.length());  // mechanisms
				size += (1 + username.length());  // username
				size += (1 + password.length());  // password

				return size;
			}

			void Domain::readProperties(const std::string& _sBuf)
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


				buf.getShortString(name);
				durable = buf.getOctet() == 1;
				buf.getShortString(url);
				buf.getShortString(mechanisms);
				buf.getShortString(username);
				buf.getShortString(password);


				delete[] _tmpBuf;
			}

			void Domain::writeProperties(std::string& _sBuf) const
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



				buf.putShortString(name);
				buf.putOctet(durable ? 1 : 0);
				buf.putShortString(url);
				buf.putShortString(mechanisms);
				buf.putShortString(username);
				buf.putShortString(password);


				uint32_t _bufLen = buf.getPosition();
				buf.reset();

				buf.getRawData(_sBuf, _bufLen);
			}

			void Domain::writeStatistics(std::string& _sBuf, bool skipHeaders)
			{
				const int _bufSize = 65536;
				char _msgChars[_bufSize];
				::qmf2::Buffer buf(_msgChars, _bufSize);

				Mutex::ScopedLock mutex(accessLock);
				instChanged = false;



				if (!skipHeaders) {
					std::string _tbuf;
					writeTimestamps(_tbuf);
					buf.putRawData(_tbuf);
				}



				// Maintenance of hi-lo statistics



				uint32_t _bufLen = buf.getPosition();
				buf.reset();

				buf.getRawData(_sBuf, _bufLen);
			}

			void Domain::doMethod(string&, const string&, string& outStr, const string&)
			{
				Manageable::status_t status = Manageable::STATUS_UNKNOWN_METHOD;
				std::string          text;

				bool _matched = false;

				const int _bufSize = 65536;
				char _msgChars[_bufSize];
				::qmf2::Buffer outBuf(_msgChars, _bufSize);



				if (!_matched) {
					outBuf.putLong(status);
					outBuf.putShortString(Manageable::StatusText(status, text));
				}

				uint32_t _bufLen = outBuf.getPosition();
				outBuf.reset();

				outBuf.getRawData(outStr, _bufLen);
			}

			std::string Domain::getKey() const
			{
				std::stringstream key;

				key << name;
				return key.str();
			}


			void Domain::mapEncodeValues(::qpid::types::Variant::Map& _map,
				bool includeProperties,
				bool includeStatistics)
			{
				using namespace ::qpid::types;
				Mutex::ScopedLock mutex(accessLock);

				if (includeProperties) {
					configChanged = false;
					_map["name"] = ::qpid::types::Variant(name);
					_map["durable"] = ::qpid::types::Variant(durable);
					_map["url"] = ::qpid::types::Variant(url);
					_map["mechanisms"] = ::qpid::types::Variant(mechanisms);
					_map["username"] = ::qpid::types::Variant(username);
					_map["password"] = ::qpid::types::Variant(password);

				}

				if (includeStatistics) {
					instChanged = false;






					// Maintenance of hi-lo statistics


				}
			}

			void Domain::mapDecodeValues(const ::qpid::types::Variant::Map& _map)
			{
				::qpid::types::Variant::Map::const_iterator _i;
				Mutex::ScopedLock mutex(accessLock);

				if ((_i = _map.find("name")) != _map.end()) {
					name = (_i->second).getString();
				}
				else {
					name = "";
				}
				if ((_i = _map.find("durable")) != _map.end()) {
					durable = _i->second;
				}
				else {
					durable = false;
				}
				if ((_i = _map.find("url")) != _map.end()) {
					url = (_i->second).getString();
				}
				else {
					url = "";
				}
				if ((_i = _map.find("mechanisms")) != _map.end()) {
					mechanisms = (_i->second).getString();
				}
				else {
					mechanisms = "";
				}
				if ((_i = _map.find("username")) != _map.end()) {
					username = (_i->second).getString();
				}
				else {
					username = "";
				}
				if ((_i = _map.find("password")) != _map.end()) {
					password = (_i->second).getString();
				}
				else {
					password = "";
				}

			}

			void Domain::doMethod(string&, const ::qpid::types::Variant::Map&, ::qpid::types::Variant::Map& outMap, const string&)
			{
				Manageable::status_t status = Manageable::STATUS_UNKNOWN_METHOD;
				std::string          text;


				outMap["_status_code"] = (uint32_t)status;
				outMap["_status_text"] = Manageable::StatusText(status, text);
			}
		}
	}
}
