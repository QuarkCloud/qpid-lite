#ifndef QPID_AMQP_0_10_CONNECTION_H
#define QPID_AMQP_0_10_CONNECTION_H

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

#include "qpid/amqp0_10/Compile.h"
#include "qpid/amqp/ConnectionInputHandler.h"
#include "qpid/amqp/ConnectionOutputHandler.h"
#include "qpid/amqp/ConnectionInputHandlerFactory.h"

#include "qpid/framing/AMQFrame.h"
#include "qpid/sys/ConnectionCodec.h"
#include "qpid/sys/Mutex.h"
#include <boost/intrusive_ptr.hpp>
#include <memory>
#include <deque>

namespace qpid {
	namespace amqp0_10 {

		class Connection : public sys::ConnectionCodec,
			public amqp::ConnectionOutputHandler
		{
			typedef std::deque<framing::AMQFrame> FrameQueue;

			FrameQueue frameQueue;
			FrameQueue workQueue;
			bool pushClosed, popClosed;
			mutable sys::Mutex frameQueueLock;
			sys::OutputControl& output;
			std::auto_ptr<amqp::ConnectionInputHandler> connection;
			std::string identifier;
			bool initialized;
			bool isClient;
			size_t buffered;
			framing::ProtocolVersion version;

		public:
			QPID_AMQP0_10_EXTERN Connection(sys::OutputControl&, const std::string& id, bool isClient);
			QPID_AMQP0_10_EXTERN void setInputHandler(std::auto_ptr<amqp::ConnectionInputHandler> c);
			size_t decode(const char* buffer, size_t size);
			size_t encode(char* buffer, size_t size);
			bool isClosed() const;
			bool canEncode();
			void abort();
			void connectionEstablished();
			void activateOutput();
			void closed();              // connection closed by peer.
			void close();               // closing from this end.
			void handle(framing::AMQFrame&);
			framing::ProtocolVersion getVersion() const;
		};
	}
}// namespace qpid::amqp0_10

#endif  /*!QPID_AMQP_0_10_CONNECTION_H*/
