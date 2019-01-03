
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
#include "qpid/broker/manage/EventFileLoadFailed.h"

namespace qpid {
	namespace broker {
		namespace manage {

			using           qpid::broker::ManagementAgent;
			using           qmf2::Manageable;
			using           qmf2::ManagementObject;
			using           qmf2::Args;
			using           qmf2::Mutex;
			using           std::string;

			string  EventFileLoadFailed::packageName = string("org.apache.qpid.acl");
			string  EventFileLoadFailed::eventName = string("fileLoadFailed");
			uint8_t EventFileLoadFailed::md5Sum[16] =
			{ 0x89,0xef,0xf2,0xca,0x80,0x2b,0x70,0x99,0x78,0x62,0x10,0x5c,0x80,0xf8,0x55,0x15 };

			EventFileLoadFailed::EventFileLoadFailed(const std::string& _userId,
				const std::string& _reason) :
				userId(_userId),
				reason(_reason)
			{}

			namespace {
				const string NAME("name");
				const string TYPE("type");
				const string DESC("desc");
				const string ARGCOUNT("argCount");
				const string ARGS("args");
			}

			void EventFileLoadFailed::registerSelf(ManagementAgent* agent)
			{
				agent->registerEvent(packageName, eventName, md5Sum, writeSchema);
			}

			void EventFileLoadFailed::writeSchema(std::string& schema)
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
				buf.putShort(2); // Argument Count

				// Arguments
				ft.clear();
				ft[NAME] = "userId";
				ft[TYPE] = TYPE_SSTR;
				buf.putMap(ft);

				ft.clear();
				ft[NAME] = "reason";
				ft[TYPE] = TYPE_LSTR;
				buf.putMap(ft);


				{
					uint32_t _len = buf.getPosition();
					buf.reset();
					buf.getRawData(schema, _len);
				}
			}

			void EventFileLoadFailed::encode(std::string& _sBuf) const
			{
				const int _bufSize = 65536;
				char _msgChars[_bufSize];
				::qmf2::Buffer buf(_msgChars, _bufSize);

				buf.putShortString(userId);
				buf.putMediumString(reason);


				uint32_t _bufLen = buf.getPosition();
				buf.reset();

				buf.getRawData(_sBuf, _bufLen);
			}

			void EventFileLoadFailed::mapEncode(::qpid::types::Variant::Map& map) const
			{
				using namespace ::qpid::types;
				map["userId"] = ::qpid::types::Variant(userId);
				map["reason"] = ::qpid::types::Variant(reason);

			}

			bool EventFileLoadFailed::match(const std::string& evt, const std::string& pkg)
			{
				return eventName == evt && packageName == pkg;
			}
		}
	}
}
