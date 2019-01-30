
#ifndef QPID_DRIVER_FUTURE_RESULT_H
#define QPID_DRIVER_FUTURE_RESULT_H 1

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



#include <string>

#include "qpid/driver/Compile.h"
#include "qpid/driver/FutureCompletion.h"

#include "qpid/framing/amqp_framing.h"


namespace qpid {
	namespace driver {

		class SessionImpl;

		///@internal
		class QPID_DRIVER_CLASS_EXTERN FutureResult : public FutureCompletion
		{
			std::string result;
		public:
			QPID_DRIVER_EXTERN const std::string& getResult(SessionImpl& session) const;
			void received(const std::string& result);
		};

	}
}
#endif  /**QPID_DRIVER_FUTURE_RESULT_H*/
