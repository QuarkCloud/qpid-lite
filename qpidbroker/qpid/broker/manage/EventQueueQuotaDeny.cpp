
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
#include "qpid/broker/manage/EventQueueQuotaDeny.h"

namespace qpid {
	namespace broker {
		namespace manage {

			using           qpid::broker::ManagementAgent;
			using           qmf2::Manageable;
			using           qmf2::ManagementObject;
			using           qmf2::Args;
			using           qmf2::Mutex;
			using           std::string;

			string  EventQueueQuotaDeny::packageName = string("org.apache.qpid.acl");
			string  EventQueueQuotaDeny::eventName = string("queueQuotaDeny");
			uint8_t EventQueueQuotaDeny::md5Sum[16] =
			{ 0x5b,0xc4,0x9f,0xc,0xb8,0x5f,0xa4,0x3d,0x7e,0xcf,0xc8,0x38,0xba,0xf,0xcd,0x98 };

			EventQueueQuotaDeny::EventQueueQuotaDeny(const std::string& _userId,
				const std::string& _queueName) :
				userId(_userId),
				queueName(_queueName)
			{}

			namespace {
				const string NAME("name");
				const string TYPE("type");
				const string DESC("desc");
				const string ARGCOUNT("argCount");
				const string ARGS("args");
			}

			void EventQueueQuotaDeny::registerSelf(ManagementAgent* agent)
			{
				agent->registerEvent(packageName, eventName, md5Sum, writeSchema);
			}

			void EventQueueQuotaDeny::writeSchema(std::string& schema)
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
				ft[NAME] = "queueName";
				ft[TYPE] = TYPE_SSTR;
				buf.putMap(ft);


				{
					uint32_t _len = buf.getPosition();
					buf.reset();
					buf.getRawData(schema, _len);
				}
			}

			void EventQueueQuotaDeny::encode(std::string& _sBuf) const
			{
				const int _bufSize = 65536;
				char _msgChars[_bufSize];
				::qmf2::Buffer buf(_msgChars, _bufSize);

				buf.putShortString(userId);
				buf.putShortString(queueName);


				uint32_t _bufLen = buf.getPosition();
				buf.reset();

				buf.getRawData(_sBuf, _bufLen);
			}

			void EventQueueQuotaDeny::mapEncode(::qpid::types::Variant::Map& map) const
			{
				using namespace ::qpid::types;
				map["userId"] = ::qpid::types::Variant(userId);
				map["queueName"] = ::qpid::types::Variant(queueName);

			}

			bool EventQueueQuotaDeny::match(const std::string& evt, const std::string& pkg)
			{
				return eventName == evt && packageName == pkg;
			}
		}
	}
}
