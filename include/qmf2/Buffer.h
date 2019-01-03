#ifndef QMF2_BUFFER_H
#define QMF2_BUFFER_H 1
/*
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
#include "qmf2/Compile.h"
#include "qpid/types/Exception.h"
#include "qpid/types/Variant.h"
#include "qpid/framing/Buffer.h"
#include <string>

namespace qmf2 {

struct OutOfBounds : qpid::types::Exception {
    OutOfBounds() : qpid::types::Exception(std::string("Out of Bounds")) {}
};


/**
 * This class is a wrapper around qpid::framing::Buffer that does not include any dependencies
 * from boost or from qpid::framing.
 */
class Buffer
{
public:
	QMF2_EXTERN Buffer(char* data=0, uint32_t size=0);
	QMF2_EXTERN ~Buffer();

	QMF2_EXTERN void reset();

	QMF2_EXTERN uint32_t available();
	QMF2_EXTERN uint32_t getSize();
	QMF2_EXTERN uint32_t getPosition();
	QMF2_EXTERN void setPosition(uint32_t);
	QMF2_EXTERN char* getPointer();

	QMF2_EXTERN void putOctet(uint8_t i);
	QMF2_EXTERN void putShort(uint16_t i);
	QMF2_EXTERN void putLong(uint32_t i);
	QMF2_EXTERN void putLongLong(uint64_t i);
	QMF2_EXTERN void putInt8(int8_t i);
	QMF2_EXTERN void putInt16(int16_t i);
	QMF2_EXTERN void putInt32(int32_t i);
	QMF2_EXTERN void putInt64(int64_t i);
	QMF2_EXTERN void putFloat(float f);
	QMF2_EXTERN void putDouble(double f);
	QMF2_EXTERN void putBin128(const uint8_t* b);

	QMF2_EXTERN uint8_t  getOctet();
	QMF2_EXTERN uint16_t getShort();
	QMF2_EXTERN uint32_t getLong();
	QMF2_EXTERN uint64_t getLongLong();
	QMF2_EXTERN int8_t   getInt8();
	QMF2_EXTERN int16_t  getInt16();
	QMF2_EXTERN int32_t  getInt32();
	QMF2_EXTERN int64_t  getInt64();
	QMF2_EXTERN float    getFloat();
	QMF2_EXTERN double   getDouble();

	QMF2_EXTERN void putShortString(const std::string& s);
	QMF2_EXTERN void putMediumString(const std::string& s);
	QMF2_EXTERN void putLongString(const std::string& s);
	QMF2_EXTERN void getShortString(std::string& s);
	QMF2_EXTERN void getMediumString(std::string& s);
	QMF2_EXTERN void getLongString(std::string& s);
	QMF2_EXTERN void getBin128(uint8_t* b);

	QMF2_EXTERN void putMap(const qpid::types::Variant::Map& map);
	QMF2_EXTERN void putList(const qpid::types::Variant::List& list);
	QMF2_EXTERN void getMap(qpid::types::Variant::Map& map);
	QMF2_EXTERN void getList(qpid::types::Variant::List& list);

	QMF2_EXTERN void putRawData(const std::string& s);
	QMF2_EXTERN void getRawData(std::string& s, uint32_t size);

	QMF2_EXTERN void putRawData(const uint8_t* data, size_t size);
	QMF2_EXTERN void getRawData(uint8_t* data, size_t size);

private:
    qpid::framing::Buffer* impl;
};

} // namespace qmf2

#endif /** QMF2_BUFFER_H */
