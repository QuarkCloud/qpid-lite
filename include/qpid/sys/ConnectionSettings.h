#ifndef QPID_SYS_CONNECTION_SETTINGS_H
#define QPID_SYS_CONNECTION_SETTINGS_H 1

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

#include "qpid/sys/Compile.h"
#include "qpid/sys/IntegerTypes.h"
#include "qpid/sys/Socket.h"
#include <string>

namespace qpid {
	namespace sys {

		/**
		 * Settings for a Connection.
		 */
		struct QPID_SYS_CLASS_EXTERN ConnectionSettings {

			QPID_SYS_EXTERN ConnectionSettings();
			QPID_SYS_EXTERN virtual ~ConnectionSettings();

			/**
			 * Allows socket to be configured; default only sets tcp-nodelay
			 * based on the flag set. Can be overridden.
			 */
			QPID_SYS_EXTERN virtual void configureSocket(qpid::sys::Socket&) const;

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
			 * If true, TCP_NODELAY will be set for the connection.
			 */
			bool tcpNoDelay;
		};
	}
}// namespace qpid::sys

#endif  /*!QPID_SYS_CONNECTION_SETTINGS_H*/
