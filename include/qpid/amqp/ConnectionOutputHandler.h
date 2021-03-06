
#ifndef QPID_AMQP_CONNECTION_OUTPUT_HANDLER_H
#define QPID_AMQP_CONNECTION_OUTPUT_HANDLER_H 1

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

#include "qpid/framing/FrameHandler.h"
#include "qpid/sys/OutputControl.h"

namespace qpid {
	namespace amqp {

		/**
		 * Provides the output handler associated with a connection.
		 */
		class ConnectionOutputHandler : public virtual qpid::framing::FrameHandler, public qpid::sys::OutputControl
		{
		public:
			virtual void close() = 0;
		};

	}
}

#endif /**QPID_AMQP_CONNECTION_OUTPUT_HANDLER_H*/
