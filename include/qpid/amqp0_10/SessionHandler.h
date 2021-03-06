#ifndef QPID_AMQP0_10_SESSION_HANDLER_H
#define QPID_AMQP0_10_SESSION_HANDLER_H 1

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
#include "qpid/driver/SessionState.h"
#include "qpid/framing/ChannelHandler.h"
#include "qpid/framing/FrameHandler.h"
#include "qpid/framing/AMQP_AllProxy.h"
#include "qpid/framing/AMQP_AllOperations.h"
#include "qpid/framing/Exception.h"

namespace qpid {
	namespace amqp0_10 {

		/**
		 * Base SessionHandler with logic common to both driver and broker.
		 *
		 * A SessionHandler is associated with a channel and can be attached
		 * to a session state.
		 */

		class QPID_AMQP0_10_CLASS_EXTERN SessionHandler : public framing::AMQP_AllOperations::SessionHandler,
			public framing::FrameHandler::InOutHandler
		{
		public:
			QPID_AMQP0_10_EXTERN SessionHandler(framing::FrameHandler* out = 0, uint16_t channel = 0);
			QPID_AMQP0_10_EXTERN ~SessionHandler();

			void setChannel(uint16_t ch) { channel = ch; }
			uint16_t getChannel() const { return channel.get(); }

			void setOutHandler(framing::FrameHandler& h) { channel.next = &h; }

			virtual driver::SessionState* getState() = 0;
			virtual framing::FrameHandler* getInHandler() = 0;

			// Non-protocol methods, called locally to initiate some action.
			QPID_AMQP0_10_EXTERN void sendDetach();
			QPID_AMQP0_10_EXTERN void sendCompletion();
			QPID_AMQP0_10_EXTERN void sendAttach(bool force);
			QPID_AMQP0_10_EXTERN void sendTimeout(uint32_t t);
			QPID_AMQP0_10_EXTERN void sendFlush();
			QPID_AMQP0_10_EXTERN void markReadyToSend();//TODO: only needed for inter-broker bridge; cleanup
			QPID_AMQP0_10_EXTERN void handleException(const qpid::framing::SessionException& e);

			/** True if the handler is ready to send and receive */
			QPID_AMQP0_10_EXTERN bool ready() const;

			// Protocol methods
			QPID_AMQP0_10_EXTERN void attach(const std::string& name, bool force);
			QPID_AMQP0_10_EXTERN void attached(const std::string& name);
			QPID_AMQP0_10_EXTERN void detach(const std::string& name);
			QPID_AMQP0_10_EXTERN void detached(const std::string& name, uint8_t code);

			QPID_AMQP0_10_EXTERN void requestTimeout(uint32_t t);
			QPID_AMQP0_10_EXTERN void timeout(uint32_t t);

			QPID_AMQP0_10_EXTERN void commandPoint(const framing::SequenceNumber& id, uint64_t offset);
			QPID_AMQP0_10_EXTERN void expected(const framing::SequenceSet& commands, const framing::Array& fragments);
			QPID_AMQP0_10_EXTERN void confirmed(const framing::SequenceSet& commands, const framing::Array& fragments);
			QPID_AMQP0_10_EXTERN void completed(const framing::SequenceSet& commands, bool timelyReply);
			QPID_AMQP0_10_EXTERN void knownCompleted(const framing::SequenceSet& commands);
			QPID_AMQP0_10_EXTERN void flush(bool expected, bool confirmed, bool completed);
			QPID_AMQP0_10_EXTERN void gap(const framing::SequenceSet& commands);

		protected:
			QPID_AMQP0_10_EXTERN virtual void invoke(const framing::AMQMethodBody& m);

			virtual void setState(const std::string& sessionName, bool force) = 0;
			virtual void connectionException(framing::connection::CloseCode code, const std::string& msg) = 0;
			virtual void channelException(framing::session::DetachCode, const std::string& msg) = 0;
			virtual void executionException(framing::execution::ErrorCode, const std::string& msg) = 0;
			virtual void detaching() = 0;

			// Notification of events
			virtual void readyToSend() {}
			virtual void readyToReceive() {}

			QPID_AMQP0_10_EXTERN virtual void handleDetach();
			QPID_AMQP0_10_EXTERN virtual void handleIn(framing::AMQFrame&);
			QPID_AMQP0_10_EXTERN virtual void handleOut(framing::AMQFrame&);

			framing::ChannelHandler channel;

		private:
			void checkAttached();
			void sendCommandPoint(const driver::SessionPoint&);

			framing::AMQP_AllProxy::Session  peer;
			std::string name;
			bool awaitingDetached;
			bool sendReady, receiveReady;
		};
	}
}// namespace qpid::amqp0_10

#endif  /*!QPID_AMQP0_10_SESSION_HANDLER_H*/
