
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
#include "qpid/broker/manage/EventQueueThresholdCrossedUpward.h"

using namespace qpid::broker::manage;
using           ::qpid::broker::ManagementAgent;
using           qmf2::Manageable;
using           qmf2::ManagementObject;
using           qmf2::Args;
using           qmf2::Mutex;
using           std::string;

string  EventQueueThresholdCrossedUpward::packageName  = string ("org.apache.qpid.broker");
string  EventQueueThresholdCrossedUpward::eventName    = string ("queueThresholdCrossedUpward");
uint8_t EventQueueThresholdCrossedUpward::md5Sum[16]   =
    {0x7d,0xc0,0x6b,0x5c,0xe2,0xc4,0xea,0xb4,0xe2,0x8d,0x2d,0x34,0x4b,0xf0,0x5d,0x72};

EventQueueThresholdCrossedUpward::EventQueueThresholdCrossedUpward (const std::string& _qName,
        const uint64_t _msgDepth,
        const uint64_t _byteDepth) :
    qName(_qName),
    msgDepth(_msgDepth),
    byteDepth(_byteDepth)
{}

namespace {
    const string NAME("name");
    const string TYPE("type");
    const string DESC("desc");
    const string ARGCOUNT("argCount");
    const string ARGS("args");
}

void EventQueueThresholdCrossedUpward::registerSelf(ManagementAgent* agent)
{
    agent->registerEvent(packageName, eventName, md5Sum, writeSchema);
}

void EventQueueThresholdCrossedUpward::writeSchema (std::string& schema)
{
    const int _bufSize = 65536;
    char _msgChars[_bufSize];
    ::qmf2::Buffer buf(_msgChars, _bufSize);
    ::qpid::types::Variant::Map ft;

    // Schema class header:
    buf.putOctet       (CLASS_KIND_EVENT);
    buf.putShortString (packageName); // Package Name
    buf.putShortString (eventName);   // Event Name
    buf.putBin128      (md5Sum);      // Schema Hash
    buf.putShort       (3); // Argument Count

    // Arguments
    ft.clear();
    ft[NAME] = "qName";
    ft[TYPE] = TYPE_SSTR;
    ft[DESC] = "Name of a queue";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "msgDepth";
    ft[TYPE] = TYPE_U64;
    ft[DESC] = "Current size of queue in messages";
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "byteDepth";
    ft[TYPE] = TYPE_U64;
    ft[DESC] = "Current size of queue in bytes";
    buf.putMap(ft);


    {
        uint32_t _len = buf.getPosition();
        buf.reset();
        buf.getRawData(schema, _len);
    }
}

void EventQueueThresholdCrossedUpward::encode(std::string& _sBuf) const
{
    const int _bufSize=65536;
    char _msgChars[_bufSize];
    ::qmf2::Buffer buf(_msgChars, _bufSize);

    buf.putShortString(qName);
    buf.putLongLong(msgDepth);
    buf.putLongLong(byteDepth);


    uint32_t _bufLen = buf.getPosition();
    buf.reset();

    buf.getRawData(_sBuf, _bufLen);
}

void EventQueueThresholdCrossedUpward::mapEncode(::qpid::types::Variant::Map& map) const
{
    using namespace ::qpid::types;
    map["qName"] = ::qpid::types::Variant(qName);
    map["msgDepth"] = ::qpid::types::Variant(msgDepth);
    map["byteDepth"] = ::qpid::types::Variant(byteDepth);

}

bool EventQueueThresholdCrossedUpward::match(const std::string& evt, const std::string& pkg)
{
    return eventName == evt && packageName == pkg;
}
