#ifndef QPID_AMQP_DECODER_H
#define QPID_AMQP_DECODER_H 1

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
#include "qpid/amqp/Compile.h"
#include "qpid/sys/IntegerTypes.h"
#include "qpid/types/Uuid.h"
#include "qpid/types/Variant.h"
#include <map>
#include <string>
#include <stddef.h>

namespace qpid {
	namespace amqp {
		struct CharSequence;
		struct Constructor;
		struct Descriptor;
		class Reader;

		/**
		 * Class to assist in decoding an AMQP encoded data-stream.
		 */
		class Decoder
		{
		public:
			QPID_AMQP_EXTERN Decoder(const char*, size_t);

			QPID_AMQP_EXTERN size_t available();
			QPID_AMQP_EXTERN uint8_t readCode();

			QPID_AMQP_EXTERN bool readBoolean();
			QPID_AMQP_EXTERN uint8_t readUByte();
			QPID_AMQP_EXTERN uint16_t readUShort();
			QPID_AMQP_EXTERN uint32_t readUInt();
			QPID_AMQP_EXTERN uint64_t readULong();
			QPID_AMQP_EXTERN int8_t readByte();
			QPID_AMQP_EXTERN int16_t readShort();
			QPID_AMQP_EXTERN int32_t readInt();
			QPID_AMQP_EXTERN int64_t readLong();
			QPID_AMQP_EXTERN float readFloat();
			QPID_AMQP_EXTERN double readDouble();
			QPID_AMQP_EXTERN qpid::types::Uuid readUuid();
			QPID_AMQP_EXTERN CharSequence readSequence8();
			QPID_AMQP_EXTERN CharSequence readSequence32();
			QPID_AMQP_EXTERN Descriptor readDescriptor();
			QPID_AMQP_EXTERN void read(Reader& reader);

			QPID_AMQP_EXTERN void readMap(qpid::types::Variant::Map&);
			QPID_AMQP_EXTERN qpid::types::Variant::Map readMap();
			QPID_AMQP_EXTERN void advance(size_t);
			QPID_AMQP_EXTERN size_t getPosition() const;
			QPID_AMQP_EXTERN void resetSize(size_t size);
			QPID_AMQP_EXTERN size_t getSize() const;

		private:
			const char* const start;
			size_t size;
			size_t position;
			size_t current;

			void readOne(Reader& reader);
			void readValue(Reader& reader, uint8_t code, const Descriptor* descriptor);
			void readList(Reader& reader, uint32_t size, uint32_t count, const Descriptor* descriptor);
			void readMap(Reader& reader, uint32_t size, uint32_t count, const Descriptor* descriptor);
			void readArray(Reader& reader, uint32_t size, uint32_t count, const Descriptor* descriptor);
			void readList8(Reader& reader, const Descriptor* descriptor);
			void readList32(Reader& reader, const Descriptor* descriptor);
			void readMap8(Reader& reader, const Descriptor* descriptor);
			void readMap32(Reader& reader, const Descriptor* descriptor);
			void readArray8(Reader& reader, const Descriptor* descriptor);
			void readArray32(Reader& reader, const Descriptor* descriptor);
			CharSequence readRawUuid();
			Constructor readConstructor();
			const char* data();
			CharSequence getCurrent(size_t remaining) const;
		};
	}
}// namespace qpid::amqp

#endif  /*!QPID_AMQP_DECODER_H*/
