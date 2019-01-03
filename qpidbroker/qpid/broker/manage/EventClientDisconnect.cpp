
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
#include "qpid/broker/manage/EventClientDisconnect.h"

using namespace qpid::broker::manage;
using           ::qpid::broker::ManagementAgent;
using           qmf2::Manageable;
using           qmf2::ManagementObject;
using           qmf2::Args;
using           qmf2::Mutex;
using           std::string;

string  EventClientDisconnect::packageName  = string ("org.apache.qpid.broker");
string  EventClientDisconnect::eventName    = string ("clientDisconnect");
uint8_t EventClientDisconnect::md5Sum[16]   =
    {0xe7,0x60,0x3e,0x45,0xc8,0x9b,0xea,0x2f,0x33,0x35,0x48,0xc0,0x98,0x3,0x69,0xdb};

EventClientDisconnect::EventClientDisconnect (const std::string& _rhost,
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

void EventClientDisconnect::registerSelf(ManagementAgent* agent)
{
    agent->registerEvent(packageName, eventName, md5Sum, writeSchema);
}

void EventClientDisconnect::writeSchema (std::string& schema)
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

void EventClientDisconnect::encode(std::string& _sBuf) const
{
    const int _bufSize=65536;
    char _msgChars[_bufSize];
    ::qmf2::Buffer buf(_msgChars, _bufSize);

    buf.putShortString(rhost);
    buf.putShortString(user);
    buf.putMap(properties);


    uint32_t _bufLen = buf.getPosition();
    buf.reset();

    buf.getRawData(_sBuf, _bufLen);
}

void EventClientDisconnect::mapEncode(::qpid::types::Variant::Map& map) const
{
    using namespace ::qpid::types;
    map["rhost"] = ::qpid::types::Variant(rhost);
    map["user"] = ::qpid::types::Variant(user);
    map["properties"] = ::qpid::types::Variant(properties);

}

bool EventClientDisconnect::match(const std::string& evt, const std::string& pkg)
{
    return eventName == evt && packageName == pkg;
}
