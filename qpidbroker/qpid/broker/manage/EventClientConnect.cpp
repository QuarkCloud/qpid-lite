
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
#include "qpid/broker/manage/EventClientConnect.h"

namespace qpid {
	namespace broker {
		namespace manage {
			using           qmf2::Manageable;
			using           qmf2::ManagementObject;
			using           qmf2::Args;
			using           qmf2::Mutex;
			using           std::string;

			string  EventClientConnect::packageName = string("org.apache.qpid.broker");
			string  EventClientConnect::eventName = string("clientConnect");
			uint8_t EventClientConnect::md5Sum[16] =
			{ 0x47,0x69,0x30,0xed,0x1,0xdd,0x96,0x29,0x7f,0x84,0xf4,0x2b,0x4b,0xb,0xc4,0x10 };

			EventClientConnect::EventClientConnect(const std::string& _rhost,
				const std::string& _user,
				const ::qpid::types::Variant::Map& _properties) :
				rhost(_rhost),
				user(_user),
				properties(_properties)
			{}

			namespace {
				const string NAME("name");
				const string TYPE("type");
				const string DESC("desc");
				const string ARGCOUNT("argCount");
				const string ARGS("args");
			}

			void EventClientConnect::registerSelf(ManagementAgent* agent)
			{
				agent->registerEvent(packageName, eventName, md5Sum, writeSchema);
			}

			void EventClientConnect::writeSchema(std::string& schema)
			{
				const int _bufSize = 65536;
				char _msgChars[_bufSize];
				::qmf2::Buffer buf(_msgChars, _bufSize);
				::qpid::types::Variant::Map ft;

				// Schema class header:
				buf.putOctet(CLASS_KIND_EVENT);
				buf.putShortString(packageName); // Package Name
				buf.putShortString(eventName);   // Event Name
				buf.putBin128(md5Sum);      // Schema Hash
				buf.putShort(3); // Argument Count

				// Arguments
				ft.clear();
				ft[NAME] = "rhost";
				ft[TYPE] = TYPE_SSTR;
				ft[DESC] = "Address (i.e. DNS name, IP address, etc.) of a remotely connected host";
				buf.putMap(ft);

				ft.clear();
				ft[NAME] = "user";
				ft[TYPE] = TYPE_SSTR;
				ft[DESC] = "Authentication identity";
				buf.putMap(ft);

				ft.clear();
				ft[NAME] = "properties";
				ft[TYPE] = TYPE_FTABLE;
				ft[DESC] = "optional identifying information sent by the remote";
				buf.putMap(ft);


				{
					uint32_t _len = buf.getPosition();
					buf.reset();
					buf.getRawData(schema, _len);
				}
			}

			void EventClientConnect::encode(std::string& _sBuf) const
			{
				const int _bufSize = 65536;
				char _msgChars[_bufSize];
				::qmf2::Buffer buf(_msgChars, _bufSize);

				buf.putShortString(rhost);
				buf.putShortString(user);
				buf.putMap(properties);


				uint32_t _bufLen = buf.getPosition();
				buf.reset();

				buf.getRawData(_sBuf, _bufLen);
			}

			void EventClientConnect::mapEncode(::qpid::types::Variant::Map& map) const
			{
				using namespace ::qpid::types;
				map["rhost"] = ::qpid::types::Variant(rhost);
				map["user"] = ::qpid::types::Variant(user);
				map["properties"] = ::qpid::types::Variant(properties);

			}

			bool EventClientConnect::match(const std::string& evt, const std::string& pkg)
			{
				return eventName == evt && packageName == pkg;
			}

		}
	}
}