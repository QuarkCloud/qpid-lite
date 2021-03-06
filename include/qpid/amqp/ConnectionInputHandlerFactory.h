#ifndef QPID_AMQP_CONNECTION_INPUT_HANDLER_FACTORY_H
#define QPID_AMQP_CONNECTION_INPUT_HANDLER_FACTORY_H 1


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

#include <boost/noncopyable.hpp>
#include <string>
#include "qpid/amqp/ConnectionInputHandler.h"
#include "qpid/amqp/ConnectionOutputHandler.h"

namespace qpid {
	namespace amqp {

		/**
		 * Callback interface used by the Acceptor to
		 * create a ConnectionInputHandler for each new connection.
		 */
		class ConnectionInputHandlerFactory : private boost::noncopyable
		{
		public:
			/**
			 *@param out handler for connection output.
			 *@param id identify the connection for management purposes.
			 */
			virtual ConnectionInputHandler* create(ConnectionOutputHandler* out,
				const std::string& id,
				bool isClient) = 0;

			virtual ~ConnectionInputHandlerFactory() {}
		};
	}
}
#endif /** QPID_AMQP_CONNECTION_INPUT_HANDLER_FACTORY_H*/
