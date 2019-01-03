#ifndef QPID_FRAMING_BUFFER_H
#define QPID_FRAMING_BUFFER_H 1

/*
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 */

#include "qpid/sys/Exception.h"
#include "qpid/framing/Compile.h"
#include "qpid/sys/IntegerTypes.h"

#include <string>

namespace qpid {
namespace framing {

struct QPID_FRAMING_CLASS_EXTERN OutOfBounds : qpid::sys::Exception {
    OutOfBounds() : qpid::sys::Exception(std::string("Out of Bounds")) {}
};

class Content;
class FieldTable;

class QPID_FRAMING_CLASS_EXTERN Buffer
{
    uint32_t size;
    char* data;
    uint32_t position;

  public:
    void checkAvailable(size_t count) { if (count > size - position) throw OutOfBounds(); }

    QPID_FRAMING_EXTERN Buffer(char* data=0, uint32_t size=0);

    QPID_FRAMING_EXTERN void reset();

    QPID_FRAMING_INLINE_EXTERN uint32_t available() const{ return size - position; }
    QPID_FRAMING_INLINE_EXTERN uint32_t getSize() const { return size; }
    QPID_FRAMING_INLINE_EXTERN uint32_t getPosition() const { return position; }
    QPID_FRAMING_INLINE_EXTERN void setPosition(uint32_t p) { position = p; }
    QPID_FRAMING_INLINE_EXTERN const char * getPointer() const { return data; }
    QPID_FRAMING_INLINE_EXTERN char* getPointer() { return data; }

    QPID_FRAMING_EXTERN void putOctet(uint8_t i);
    QPID_FRAMING_EXTERN void putShort(uint16_t i);
    QPID_FRAMING_EXTERN void putLong(uint32_t i);
    QPID_FRAMING_EXTERN void putLongLong(uint64_t i);
    QPID_FRAMING_EXTERN void putInt8(int8_t i);
    QPID_FRAMING_EXTERN void putInt16(int16_t i);
    QPID_FRAMING_EXTERN void putInt32(int32_t i);
    QPID_FRAMING_EXTERN void putInt64(int64_t i);
    QPID_FRAMING_EXTERN void putFloat(float f);
    QPID_FRAMING_EXTERN void putDouble(double f);
    QPID_FRAMING_EXTERN void putBin128(const uint8_t* b);

    QPID_FRAMING_EXTERN uint8_t  getOctet();
    QPID_FRAMING_EXTERN uint16_t getShort();
    QPID_FRAMING_EXTERN uint32_t getLong();
    QPID_FRAMING_EXTERN uint64_t getLongLong();
    QPID_FRAMING_EXTERN int8_t   getInt8();
    QPID_FRAMING_EXTERN int16_t  getInt16();
    QPID_FRAMING_EXTERN int32_t  getInt32();
    QPID_FRAMING_EXTERN int64_t  getInt64();
    QPID_FRAMING_EXTERN float    getFloat();
    QPID_FRAMING_EXTERN double   getDouble();

    template <int n>
    QPID_FRAMING_EXTERN uint64_t getUInt();

    template <int n>
    QPID_FRAMING_EXTERN void putUInt(uint64_t);

    QPID_FRAMING_EXTERN void putShortString(const std::string& s);
    QPID_FRAMING_EXTERN void putMediumString(const std::string& s);
    QPID_FRAMING_EXTERN void putLongString(const std::string& s);
    QPID_FRAMING_EXTERN void getShortString(std::string& s);
    QPID_FRAMING_EXTERN void getMediumString(std::string& s);
    QPID_FRAMING_EXTERN void getLongString(std::string& s);
    QPID_FRAMING_EXTERN void getBin128(uint8_t* b);

    QPID_FRAMING_EXTERN void putRawData(const std::string& s);
    QPID_FRAMING_EXTERN void getRawData(std::string& s, uint32_t size);

    QPID_FRAMING_EXTERN void putRawData(const uint8_t* data, size_t size);
    QPID_FRAMING_EXTERN void getRawData(uint8_t* data, size_t size);

    template <class T> void put(const T& data) { data.encode(*this); }
    template <class T> void get(T& data) { data.decode(*this); }

    QPID_FRAMING_EXTERN void dump(std::ostream&) const;
};

std::ostream& operator<<(std::ostream&, const Buffer&);

}} // namespace qpid::framing


#endif
