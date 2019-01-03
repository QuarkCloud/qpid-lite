#ifndef QPID_BROKER_SESSION_HANDLER_H
#define QPID_BROKER_SESSION_HANDLER_H 1

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
#include "qpid/broker/Compile.h"
#include "qpid/base/amqp0_10/SessionHandler.h"
#include "qpid/broker/amqp0_10/Connection.h"
#include "qpid/broker/SessionHandler.h"
#include "qpid/broker/SessionState.h"
#include "qpid/framing/AMQP_ClientProxy.h"
#include <boost/shared_ptr.hpp>

namespace qpid {
	namespace broker {

		/**
		 * A SessionHandler is associated with each active channel. It
		 * receives incoming frames, handles session controls and manages the
		 * association between the channel and a session.
		 */
		class SessionHandler : public ::qpid::base::amqp0_10::SessionHandler {
		public:
			class ErrorListener {
			public:
				virtual ~ErrorListener() {}

				/** Called when there is an outgoing connection-exception */
				virtual void connectionException(
					framing::connection::CloseCode code, const std::string& msg) = 0;
				/** Called when there is an outgoing channel-exception */
				virtual void channelException(
					framing::session::DetachCode, const std::string& msg) = 0;
				/** Called when there is an outgoing execution-exception */
				virtual void executionException(
					framing::execution::ErrorCode, const std::string& msg) = 0;

				/** Called when there is an incoming execution-exception.
				 * Useful for inter-broker bridges.
				 */
				virtual void incomingExecutionException(
					framing::execution::ErrorCode, const std::string& msg) = 0;

				/** Called when it is safe to delete the ErrorListener. */
				virtual void detach() = 0;
			};

			/**
			 *@param e must not be deleted until ErrorListener::detach has been called */
			SessionHandler(broker::amqp0_10::Connection&, framing::ChannelId);
			~SessionHandler();

			/** Get broker::SessionState */
			base::SessionState* getSession() { return session.get(); }
			const base::SessionState* getSession() const { return session.get(); }

			QPID_BROKER_EXTERN broker::amqp0_10::Connection& getConnection();
			QPID_BROKER_EXTERN const broker::amqp0_10::Connection& getConnection() const;

			framing::AMQP_ClientProxy& getProxy() { return proxy; }
			const framing::AMQP_ClientProxy& getProxy() const { return proxy; }

			virtual void handleDetach();
			void attached(const std::string& name);//used by 'pushing' inter-broker bridges
			void attachAs(const std::string& name);//used by 'pulling' inter-broker bridges

			QPID_BROKER_EXTERN void setErrorListener(boost::shared_ptr<ErrorListener> e) { errorListener = e; }

			// Called by SessionAdapter
			void incomingExecutionException(framing::execution::ErrorCode, const std::string& msg);

		protected:
			void setState(const std::string& sessionName, bool force);
			qpid::base::SessionState* getState();
			framing::FrameHandler* getInHandler();
			void connectionException(framing::connection::CloseCode code, const std::string& msg);
			void channelException(framing::session::DetachCode, const std::string& msg);
			void executionException(framing::execution::ErrorCode, const std::string& msg);
			void detaching();
			void readyToSend();

		private:
			struct SetChannelProxy : public framing::AMQP_ClientProxy { // Proxy that sets the channel.
				framing::ChannelHandler setChannel;
				SetChannelProxy(uint16_t ch, framing::FrameHandler* out)
					: framing::AMQP_ClientProxy(setChannel), setChannel(ch, out) {}
			};

			broker::amqp0_10::Connection& connection;
			framing::AMQP_ClientProxy proxy;
			std::auto_ptr<broker::SessionState> session;
			boost::shared_ptr<ErrorListener> errorListener;
		};

	}
}// namespace qpid::broker

#endif  /*!QPID_BROKER_SESSION_HANDLER_H*/
