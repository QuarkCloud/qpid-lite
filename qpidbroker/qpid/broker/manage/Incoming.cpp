
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
#include "qpid/broker/manage/Incoming.h"


#include "qpid/log/Statement.h"

#include <iostream>
#include <sstream>
#include <string.h>

using namespace qpid::broker::manage;
using           ::qpid::broker::ManagementAgent;
using           qmf2::Manageable;
using           qmf2::ManagementObject;
using           qmf2::Args;
using           qmf2::Mutex;
using           std::string;

string  Incoming::packageName  = string ("org.apache.qpid.broker");
string  Incoming::className    = string ("incoming");
uint8_t Incoming::md5Sum[MD5_LEN]   =
    {0xf6,0x65,0xb4,0xd2,0x9a,0xfe,0x7,0xce,0x86,0xd4,0x24,0x18,0x14,0x61,0xef,0x42};

Incoming::Incoming (ManagementAgent*, Manageable* _core, ::qmf2::Manageable* _parent, const std::string& _containerid, const std::string& _name, const std::string& _source, const std::string& _target, const std::string& _domain) :
    ManagementObject(_core),containerid(_containerid),name(_name),source(_source),target(_target),domain(_domain)
{
    sessionRef = _parent->GetManagementObject()->getObjectId();



    perThreadStatsArray = new struct PerThreadStats*[maxThreads];
    for (int idx = 0; idx < maxThreads; idx++)
        perThreadStatsArray[idx] = 0;


    QPID_LOG_CAT(trace, model, "Mgmt create " << className
        << ". id:" << getKey());

}

Incoming::~Incoming ()
{

    for (int idx = 0; idx < maxThreads; idx++)
        if (perThreadStatsArray[idx] != 0)
            delete perThreadStatsArray[idx];
    delete[] perThreadStatsArray;

}

void Incoming::debugStats (const std::string& comment)
{

    bool logEnabled;
    QPID_LOG_TEST_CAT(trace, model, logEnabled);
    if (logEnabled)
    {
        ::qpid::types::Variant::Map map;
        mapEncodeValues(map, false, true);
        QPID_LOG_CAT(trace, model, "Mgmt " << comment << ((comment!="")?(" "):("")) << className
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

void Incoming::registerSelf(ManagementAgent* agent)
{
    agent->registerClass(packageName, className, md5Sum, writeSchema);
}

void Incoming::writeSchema (std::string& schema)
{
    const int _bufSize=65536;
    char _msgChars[_bufSize];
    ::qmf2::Buffer buf(_msgChars, _bufSize);
    ::qpid::types::Variant::Map ft;

    // Schema class header:
    buf.putOctet       (CLASS_KIND_TABLE);
    buf.putShortString (packageName); // Package Name
    buf.putShortString (className);   // Class Name
    buf.putBin128      (md5Sum);      // Schema Hash
    buf.putShort       (6); // Config Element Count
    buf.putShort       (1); // Inst Element Count
    buf.putShort       (0); // Method Count

    // Properties
    ft.clear();
    ft[NAME] = "sessionRef";
    ft[TYPE] = TYPE_REF;
    ft[ACCESS] = ACCESS_RC;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 0;
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "containerid";
    ft[TYPE] = TYPE_SSTR;
    ft[ACCESS] = ACCESS_RC;
    ft[IS_INDEX] = 1;
    ft[IS_OPTIONAL] = 0;
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "name";
    ft[TYPE] = TYPE_SSTR;
    ft[ACCESS] = ACCESS_RC;
    ft[IS_INDEX] = 1;
    ft[IS_OPTIONAL] = 0;
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "source";
    ft[TYPE] = TYPE_SSTR;
    ft[ACCESS] = ACCESS_RC;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 0;
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "target";
    ft[TYPE] = TYPE_SSTR;
    ft[ACCESS] = ACCESS_RC;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 0;
    buf.putMap(ft);

    ft.clear();
    ft[NAME] = "domain";
    ft[TYPE] = TYPE_SSTR;
    ft[ACCESS] = ACCESS_RC;
    ft[IS_INDEX] = 0;
    ft[IS_OPTIONAL] = 0;
    buf.putMap(ft);


    // Statistics
    ft.clear();
    ft[NAME] = "transfers";
    ft[TYPE] = TYPE_U64;
    ft[UNIT] = "message";
    ft[DESC] = "Messages transfered";
    buf.putMap(ft);


    // Methods

    {
        uint32_t _len = buf.getPosition();
        buf.reset();
        buf.getRawData(schema, _len);
    }
}


void Incoming::aggregatePerThreadStats(struct PerThreadStats* totals) const
{
    totals->transfers = 0;

    for (int idx = 0; idx < maxThreads; idx++) {
        struct PerThreadStats* threadStats = perThreadStatsArray[idx];
        if (threadStats != 0) {
            totals->transfers += threadStats->transfers;

        }
    }
}



uint32_t Incoming::writePropertiesSize() const
{
    uint32_t size = writeTimestampsSize();

    size += 16;  // sessionRef
    size += (1 + containerid.length());  // containerid
    size += (1 + name.length());  // name
    size += (1 + source.length());  // source
    size += (1 + target.length());  // target
    size += (1 + domain.length());  // domain

    return size;
}

void Incoming::readProperties (const std::string& _sBuf)
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


    {std::string _s; buf.getRawData(_s, sessionRef.encodedSize()); sessionRef.decode(_s);};
    buf.getShortString(containerid);
    buf.getShortString(name);
    buf.getShortString(source);
    buf.getShortString(target);
    buf.getShortString(domain);


    delete [] _tmpBuf;
}

void Incoming::writeProperties (std::string& _sBuf) const
{
    const int _bufSize=65536;
    char _msgChars[_bufSize];
    ::qmf2::Buffer buf(_msgChars, _bufSize);

    Mutex::ScopedLock mutex(accessLock);
    configChanged = false;

    {
        std::string _tbuf;
        writeTimestamps(_tbuf);
        buf.putRawData(_tbuf);
    }



    {std::string _s; sessionRef.encode(_s); buf.putRawData(_s);};
    buf.putShortString(containerid);
    buf.putShortString(name);
    buf.putShortString(source);
    buf.putShortString(target);
    buf.putShortString(domain);


    uint32_t _bufLen = buf.getPosition();
    buf.reset();

    buf.getRawData(_sBuf, _bufLen);
}

void Incoming::writeStatistics (std::string& _sBuf, bool skipHeaders)
{
    const int _bufSize=65536;
    char _msgChars[_bufSize];
    ::qmf2::Buffer buf(_msgChars, _bufSize);

    Mutex::ScopedLock mutex(accessLock);
    instChanged = false;


    struct PerThreadStats totals;
    aggregatePerThreadStats(&totals);


    if (!skipHeaders) {
        std::string _tbuf;
        writeTimestamps (_tbuf);
        buf.putRawData(_tbuf);
    }

    buf.putLongLong(totals.transfers);


    // Maintenance of hi-lo statistics



    uint32_t _bufLen = buf.getPosition();
    buf.reset();

    buf.getRawData(_sBuf, _bufLen);
}

void Incoming::doMethod (string&, const string&, string& outStr, const string&)
{
    Manageable::status_t status = Manageable::STATUS_UNKNOWN_METHOD;
    std::string          text;

    bool _matched = false;

    const int _bufSize=65536;
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

std::string Incoming::getKey() const
{
    std::stringstream key;

    key << containerid << ",";
    key << name;
    return key.str();
}


void Incoming::mapEncodeValues (::qpid::types::Variant::Map& _map,
                                              bool includeProperties,
                                              bool includeStatistics)
{
    using namespace ::qpid::types;
    Mutex::ScopedLock mutex(accessLock);

    if (includeProperties) {
        configChanged = false;
    _map["sessionRef"] = ::qpid::types::Variant(sessionRef);
    _map["containerid"] = ::qpid::types::Variant(containerid);
    _map["name"] = ::qpid::types::Variant(name);
    _map["source"] = ::qpid::types::Variant(source);
    _map["target"] = ::qpid::types::Variant(target);
    _map["domain"] = ::qpid::types::Variant(domain);

    }

    if (includeStatistics) {
        instChanged = false;


        struct PerThreadStats totals;
        aggregatePerThreadStats(&totals);



    _map["transfers"] = ::qpid::types::Variant(totals.transfers);


    // Maintenance of hi-lo statistics


    }
}

void Incoming::mapDecodeValues (const ::qpid::types::Variant::Map& _map)
{
    ::qpid::types::Variant::Map::const_iterator _i;
    Mutex::ScopedLock mutex(accessLock);

    if ((_i = _map.find("sessionRef")) != _map.end()) {
        sessionRef = _i->second;
    } else {
        sessionRef = ::qmf2::ObjectId();
    }
    if ((_i = _map.find("containerid")) != _map.end()) {
        containerid = (_i->second).getString();
    } else {
        containerid = "";
    }
    if ((_i = _map.find("name")) != _map.end()) {
        name = (_i->second).getString();
    } else {
        name = "";
    }
    if ((_i = _map.find("source")) != _map.end()) {
        source = (_i->second).getString();
    } else {
        source = "";
    }
    if ((_i = _map.find("target")) != _map.end()) {
        target = (_i->second).getString();
    } else {
        target = "";
    }
    if ((_i = _map.find("domain")) != _map.end()) {
        domain = (_i->second).getString();
    } else {
        domain = "";
    }

}

void Incoming::doMethod (string&, const ::qpid::types::Variant::Map&, ::qpid::types::Variant::Map& outMap, const string&)
{
    Manageable::status_t status = Manageable::STATUS_UNKNOWN_METHOD;
    std::string          text;


    outMap["_status_code"] = (uint32_t) status;
    outMap["_status_text"] = Manageable::StatusText(status, text);
}
