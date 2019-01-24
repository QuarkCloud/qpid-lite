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
#include "qpid/amqp1_0/SaslServer.h"
#include "qpid/amqp/Constructor.h"
#include "qpid/amqp/Decoder.h"
#include "qpid/amqp/Descriptor.h"
#include "qpid/amqp/descriptors.h"
#include "qpid/amqp/Encoder.h"
#include "qpid/amqp/typecodes.h"
#include "qpid/sys/Statement.h"
#include "qpid/sys/StringUtils.h"
#include <limits>
#include <vector>


namespace qpid {
	namespace amqp1_0 {
		namespace {
			const std::string SPACE(" ");
			const std::string NULL_("NULL");
		}

		SaslServer::SaslServer(const std::string& id) : SaslReader(id) {}
		SaslServer::~SaslServer() {}

		void SaslServer::mechanisms(const std::string& mechanisms)
		{
			void* frameToken = startFrame();

			std::vector<std::string> parts = sys::split(mechanisms, SPACE);
			void* listToken = encoder.startList32(&amqp::sasl::SASL_MECHANISMS);
			if (parts.size() > 1) {
				void* arrayToken = encoder.startArray8(amqp::Constructor(amqp::typecodes::SYMBOL8));
				for (std::vector<std::string>::const_iterator i = parts.begin(); i != parts.end(); ++i) {
					uint8_t size = (uint8_t)i->size() > std::numeric_limits<uint8_t>::max() ? std::numeric_limits<uint8_t>::max() : (uint8_t)i->size();
					encoder.write(size);
					encoder.writeBytes(i->data(), size);
				}
				encoder.endArray8(parts.size(), arrayToken);
			}
			else {
				encoder.writeSymbol(mechanisms);
			}
			encoder.endList32(1, listToken);

			endFrame(frameToken);
			QPID_LOG_CAT(debug, protocol, id << " Sent SASL-MECHANISMS(" << mechanisms << ") " << encoder.getPosition());
		}
		void SaslServer::challenge(const std::string* c)
		{
			void* frameToken = startFrame();

			void* listToken = encoder.startList32(&amqp::sasl::SASL_CHALLENGE);
			if (c) encoder.writeBinary(*c);
			else encoder.writeNull();
			encoder.endList32(1, listToken);

			endFrame(frameToken);
			QPID_LOG_CAT(debug, protocol, id << " Sent SASL-CHALLENGE(" << (c ? *c : NULL_) << ") " << encoder.getPosition());
		}
		void SaslServer::completed(bool succeeded)
		{
			void* frameToken = startFrame();

			void* listToken = encoder.startList8(&amqp::sasl::SASL_OUTCOME);
			encoder.writeUByte(succeeded ? 0 : 1);
			encoder.endList8(1, listToken);

			endFrame(frameToken);
			QPID_LOG_CAT(debug, protocol, id << " Sent SASL-OUTCOME(" << (succeeded ? 0 : 1) << ") " << encoder.getPosition());
		}

		namespace {
			class SaslInitReader : public amqp::Reader
			{
			public:
				SaslInitReader(SaslServer& s, uint32_t e) : server(s), expected(e), hasResponse(false), index(0) {}
				void onNull(const amqp::Descriptor*)
				{
					++index;
					if (index == 2) {
						if (--expected == 0) {
							server.init(mechanism, 0, 0);
						}
					}
					else if (index == 3) {
						server.init(mechanism, hasResponse ? &response : 0, 0);
					}
					else {
						QPID_LOG(warning, "Unexpected sequence of fields for SASL-INIT: got null for field " << index);
					}
				}
				void onBinary(const amqp::CharSequence& r, const amqp::Descriptor*)
				{
					if (++index != 2) QPID_LOG(warning, "Unexpected sequence of fields for SASL-INIT: got binary for field " << index);
					response = r.str();
					hasResponse = true;
					if (--expected == 0) {
						server.init(mechanism, &response, 0);
					}
				}
				void onString(const amqp::CharSequence& h, const amqp::Descriptor*)
				{
					if (--expected || ++index != 3) {
						QPID_LOG(warning, "Unexpected sequence of fields for SASL-INIT: got string for field " << index);
					}
					else {
						std::string hostname = h.str();
						server.init(mechanism, hasResponse ? &response : 0, &hostname);
					}
				}
				void onSymbol(const amqp::CharSequence& m, const amqp::Descriptor*)
				{
					if (++index != 1) QPID_LOG(warning, "Unexpected sequence of fields for SASL-INIT: got symbol for field " << index);
					if (--expected) {
						mechanism = m.str();
					}
					else {
						server.init(m.str(), 0, 0);
					}
				}
			private:
				SaslServer& server;
				uint32_t expected;
				std::string mechanism;
				std::string response;
				bool hasResponse;
				uint32_t index;
			};

			class SaslResponseReader : public amqp::Reader
			{
			public:
				SaslResponseReader(SaslServer& s) : server(s) {}
				void onNull(const amqp::Descriptor*) { server.response(0); }
				void onBinary(const amqp::CharSequence& r, const amqp::Descriptor*)
				{
					std::string s = r.str();
					server.response(&s);
				}
			private:
				SaslServer& server;
			};
		}

		bool SaslServer::onStartList(uint32_t count, const amqp::CharSequence& arguments, 
			const amqp::CharSequence& /*full raw data*/, const amqp::Descriptor* descriptor)
		{
			if (!descriptor) {
				QPID_LOG(error, "Expected described type in SASL negotiation but got no descriptor");
			}
			else if (descriptor->match(amqp::sasl::SASL_INIT_SYMBOL, amqp::sasl::SASL_INIT_CODE)) {
				QPID_LOG(trace, "Reading SASL-INIT");
				amqp::Decoder decoder(arguments.data, arguments.size);
				if (count < 1 || count > 3) QPID_LOG(error, "Invalid SASL-INIT frame; got " << count << " fields");
				SaslInitReader reader(*this, count);
				decoder.read(reader);
			}
			else if (descriptor->match(amqp::sasl::SASL_RESPONSE_SYMBOL, amqp::sasl::SASL_RESPONSE_CODE)) {
				QPID_LOG(trace, "Reading SASL-RESPONSE (" << std::string(arguments.data, arguments.size) << ") " << count << " elements");
				amqp::Decoder decoder(arguments.data, arguments.size);
				if (count != 1) QPID_LOG(error, "Invalid SASL-RESPONSE frame; exactly one field expected, got " << count);
				SaslResponseReader reader(*this);
				decoder.read(reader);
			}
			else {
				QPID_LOG(error, "Unexpected descriptor in SASL negotiation: " << *descriptor);
			}
			return false;
		}
	}
}// namespace qpid::amqp1_0
