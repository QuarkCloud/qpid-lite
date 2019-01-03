#ifndef QPID_SYS_NULL_SASL_SERVER_H
#define QPID_SYS_NULL_SASL_SERVER_H 1

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
#include "qpid/sys/SaslServer.h"

namespace qpid {
	namespace sys {
		/**
		 * Dummy implementation of the SASL server role. This will advertise
		 * ANONYMOUS and PLAIN, and parse the reponse data for those
		 * accordingly, but will make no attempt to actually authenticate
		 * users.
		 */
		class NullSaslServer : public SaslServer
		{
		public:
			QPID_SYS_EXTERN NullSaslServer(const std::string& realm);
			Status start(const std::string& mechanism, const std::string* response, std::string& challenge);
			Status step(const std::string* response, std::string& challenge);
			std::string getMechanisms();
			std::string getUserid();
			std::auto_ptr<qpid::sys::SecurityLayer> getSecurityLayer(size_t);
		private:
			std::string realm;
			std::string userid;
		};
	}
} // namespace qpid

#endif  /*!QPID_SYS_NULL_SASL_SERVER_H*/