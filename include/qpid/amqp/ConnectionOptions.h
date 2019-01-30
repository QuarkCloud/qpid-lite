#ifndef QPID_AMQP_CONNECTION_OPTIONS_H
#define QPID_AMQP_CONNECTION_OPTIONS_H 1

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
#include "qpid/framing/FieldTable.h"
#include "qpid/types/Variant.h"
#include "qpid/sys/IntegerTypes.h"
#include "qpid/sys/ConnectionSettings.h"
#include <map>
#include <vector>
#include <string>
#include <boost/optional.hpp>

namespace qpid {
	namespace amqp {

		class ConnectionOptions : public qpid::sys::ConnectionSettings{
		public:
			std::vector<std::string> urls;
			bool replaceUrls;
			bool reconnect;
			double timeout;
			int32_t limit;
			double minReconnectInterval;
			double maxReconnectInterval;
			int32_t retries;
			bool reconnectOnLimitExceeded;
			std::string identifier;
			bool nestAnnotations;
			bool setToOnSend;
			boost::optional<bool> addressPassthrough;
			uint32_t maxDeliveryAttempts;
			bool raiseRejected;
			double redeliveryTimeout;
			std::map<std::string, qpid::types::Variant> properties;

			/**
			 * The protocol used for the connection (defaults to 'tcp')
			 */
			std::string protocol;

			/**
			 * The host (or ip address) to connect to (defaults to 'localhost').
			 */
			std::string host;
			/**
			 * The port to connect to (defaults to 5672).
			 */
			uint16_t port;
			/**
			 * Allows an AMQP 'virtual host' to be specified for the
			 * connection.
			 */
			std::string virtualhost;

			/**
			 * The username to use when authenticating the connection. If not
			 * specified the current users login is used if available.
			 */
			std::string username;
			/**
			 * The password to use when authenticating the connection.
			 */
			std::string password;
			/**
			 * The SASL mechanism to use when authenticating the connection;
			 * the options are currently PLAIN or ANONYMOUS.
			 */
			std::string mechanism;
			/**
			 * Allows a locale to be specified for the connection.
			 */
			std::string locale;
			/**
			 * Allows a heartbeat frequency to be specified
			 */
			uint16_t heartbeat;
			/**
			 * The maximum number of channels that the client will request for
			 * use on this connection.
			 */
			uint16_t maxChannels;
			/**
			 * The maximum frame size that the client will request for this
			 * connection.
			 */
			uint16_t maxFrameSize;
			/**
			 * Limit the size of the connections send buffer . The buffer
			 * is limited to bounds * maxFrameSize.
			 */
			unsigned int bounds;
			/**
			 * If true, TCP_NODELAY will be set for the connection.
			 */
			bool tcpNoDelay;
			/**
			 * SASL service name
			 */
			std::string service;
			/**
			 * Minimum acceptable strength of any SASL negotiated security
			 * layer. 0 means no security layer required.
			 */
			unsigned int minSsf;
			/**
			 * Maximum acceptable strength of any SASL negotiated security
			 * layer. 0 means no security layer allowed.
			 */
			unsigned int maxSsf;
			/**
			 * SSL cert-name for the connection. Overrides global SSL
			 * settings. Used only when a client connects to the broker.
			 */
			std::string sslCertName;

			/**
			 * Passed as client-propreties on opening the connecction.
			 */
			framing::FieldTable clientProperties;

			/**
			 * If using SSL, connect regardless of hostname verification failure.
			 */
			bool sslIgnoreHostnameVerificationFailure;

			QPID_AMQP_EXTERN ConnectionOptions();
			QPID_AMQP_EXTERN ConnectionOptions(const std::map<std::string, qpid::types::Variant>&);

			QPID_AMQP_EXTERN void set(const std::string& name, const qpid::types::Variant& value);
		private:
			void InternalInit();
		};
	}
}// namespace qpid::amqp

#endif  /*!QPID_AMQP_CONNECTION_OPTIONS_H*/
