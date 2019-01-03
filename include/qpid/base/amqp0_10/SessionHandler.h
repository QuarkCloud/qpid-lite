#ifndef QPID_BASE_AMQP0_10_SESSION_HANDLER_H
#define QPID_BASE_AMQP0_10_SESSION_HANDLER_H 1

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

#include "qpid/framing/ChannelHandler.h"
#include "qpid/framing/AMQP_AllProxy.h"
#include "qpid/framing/AMQP_AllOperations.h"
#include "qpid/framing/Exception.h"
#include "qpid/base/SessionState.h"
#include "qpid/base/Compile.h"

namespace qpid {
	namespace base {

		namespace amqp0_10 {

			/**
			 * Base SessionHandler with logic common to both client and broker.
			 *
			 * A SessionHandler is associated with a channel and can be attached
			 * to a session state.
			 */

			class QPID_BASE_CLASS_EXTERN SessionHandler : public ::qpid::framing::AMQP_AllOperations::SessionHandler,
				public ::qpid::framing::FrameHandler::InOutHandler
			{
			public:
				QPID_BASE_EXTERN SessionHandler(::qpid::framing::FrameHandler* out = 0, uint16_t channel = 0);
				QPID_BASE_EXTERN ~SessionHandler();

				void setChannel(uint16_t ch) { channel = ch; }
				uint16_t getChannel() const { return channel.get(); }

				void setOutHandler(framing::FrameHandler& h) { channel.next = &h; }

				virtual SessionState* getState() = 0;
				virtual framing::FrameHandler* getInHandler() = 0;

				// Non-protocol methods, called locally to initiate some action.
				QPID_BASE_EXTERN void sendDetach();
				QPID_BASE_EXTERN void sendCompletion();
				QPID_BASE_EXTERN void sendAttach(bool force);
				QPID_BASE_EXTERN void sendTimeout(uint32_t t);
				QPID_BASE_EXTERN void sendFlush();
				QPID_BASE_EXTERN void markReadyToSend();//TODO: only needed for inter-broker bridge; cleanup
				QPID_BASE_EXTERN void handleException(const qpid::framing::SessionException& e);

				/** True if the handler is ready to send and receive */
				QPID_BASE_EXTERN bool ready() const;

				// Protocol methods
				QPID_BASE_EXTERN void attach(const std::string& name, bool force);
				QPID_BASE_EXTERN void attached(const std::string& name);
				QPID_BASE_EXTERN void detach(const std::string& name);
				QPID_BASE_EXTERN void detached(const std::string& name, uint8_t code);

				QPID_BASE_EXTERN void requestTimeout(uint32_t t);
				QPID_BASE_EXTERN void timeout(uint32_t t);

				QPID_BASE_EXTERN void commandPoint(const framing::SequenceNumber& id, uint64_t offset);
				QPID_BASE_EXTERN void expected(const framing::SequenceSet& commands, const framing::Array& fragments);
				QPID_BASE_EXTERN void confirmed(const framing::SequenceSet& commands, const framing::Array& fragments);
				QPID_BASE_EXTERN void completed(const framing::SequenceSet& commands, bool timelyReply);
				QPID_BASE_EXTERN void knownCompleted(const framing::SequenceSet& commands);
				QPID_BASE_EXTERN void flush(bool expected, bool confirmed, bool completed);
				QPID_BASE_EXTERN void gap(const framing::SequenceSet& commands);

			protected:
				QPID_BASE_EXTERN virtual void invoke(const framing::AMQMethodBody& m);

				virtual void setState(const std::string& sessionName, bool force) = 0;
				virtual void connectionException(framing::connection::CloseCode code, const std::string& msg) = 0;
				virtual void channelException(framing::session::DetachCode, const std::string& msg) = 0;
				virtual void executionException(framing::execution::ErrorCode, const std::string& msg) = 0;
				virtual void detaching() = 0;

				// Notification of events
				virtual void readyToSend() {}
				virtual void readyToReceive() {}

				QPID_BASE_EXTERN virtual void handleDetach();
				QPID_BASE_EXTERN virtual void handleIn(framing::AMQFrame&);
				QPID_BASE_EXTERN virtual void handleOut(framing::AMQFrame&);

				framing::ChannelHandler channel;

			private:
				void checkAttached();
				void sendCommandPoint(const SessionPoint&);

				framing::AMQP_AllProxy::Session  peer;
				std::string name;
				bool awaitingDetached;
				bool sendReady, receiveReady;
			};
		}
	}
}// namespace qpid::base::amqp0_10

#endif  /*!QPID_BASE_AMQP0_10_SESSION_HANDLER_H*/
