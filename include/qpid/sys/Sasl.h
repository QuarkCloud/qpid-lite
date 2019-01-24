#ifndef QPID_SYS_SASL_H
#define QPID_SYS_SASL_H 1

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

#include <memory>
#include <string>
#include "qpid/sys/Compile.h"
#include "qpid/sys/IntegerTypes.h"
#include "qpid/sys/SecurityLayer.h"
#include "qpid/sys/SecuritySettings.h"

namespace qpid {
	namespace sys {

		/**
		 * Interface to support for the SASL client role. This class is implemented by platform-specific
		 * SASL providers.
		 */
		class Sasl
		{
		public:
			/**
			 * Start SASL negotiation with the broker.
			 *
			 * @param mechanisms Comma-separated list of the SASL mechanism the
			 *             client supports.
			 * @param externalSecuritySettings security related details from the underlying transport
			 */
			virtual bool start(const std::string& mechanisms, std::string& response,
				const qpid::sys::SecuritySettings* externalSecuritySettings = 0) = 0;
			virtual std::string step(const std::string& challenge) = 0;
			virtual std::string getMechanism() = 0;
			virtual std::string getUserId() = 0;
			virtual std::auto_ptr<qpid::sys::SecurityLayer> getSecurityLayer(uint16_t maxFrameSize) = 0;
			QPID_SYS_EXTERN virtual ~Sasl() {}
		};
	}
} // namespace qpid

#endif  /*!QPID_SYS_SASL_H*/
