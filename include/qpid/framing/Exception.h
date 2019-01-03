#ifndef QPID_FRAMING_EXCEPTION_H
#define QPID_FRAMING_EXCEPTION_H 1

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

#include "qpid/framing/amqp_types.h"
#include "qpid/framing/constants.h"
#include "qpid/framing/enum.h"
#include "qpid/framing/Compile.h"
#include "qpid/sys/StrError.h"
#include "qpid/sys/Exception.h"
#include <string>
#include <errno.h>

namespace qpid{
	namespace framing {

		struct QPID_FRAMING_CLASS_EXTERN SessionException : public qpid::sys::Exception {
			const framing::execution::ErrorCode code;
			SessionException(framing::execution::ErrorCode code_, const std::string& message)
				: qpid::sys::Exception(message), code(code_) {}
		};

		struct QPID_FRAMING_CLASS_EXTERN ChannelException : public qpid::sys::Exception {
			const framing::session::DetachCode code;
			ChannelException(framing::session::DetachCode _code, const std::string& message)
				: qpid::sys::Exception(message), code(_code) {}
		};

		struct QPID_FRAMING_CLASS_EXTERN ConnectionException : public qpid::sys::Exception {
			const framing::connection::CloseCode code;
			ConnectionException(framing::connection::CloseCode _code, const std::string& message)
				: qpid::sys::Exception(message), code(_code) {}
		};

		/**
		 * Exception representing transport failure
		 */
		/*
		struct QPID_FRAMING_CLASS_EXTERN TransportFailure : public qpid::sys::Exception {
			TransportFailure(const std::string& msg = std::string()) : qpid::sys::Exception(msg) {}
		};

		struct QPID_FRAMING_CLASS_EXTERN ProtocolVersionError : public TransportFailure {
			ProtocolVersionError(const std::string& msg = std::string()) : TransportFailure(msg) {}
		};
		*/
	}
} // namespace qpid

#endif  /*!QPID_FRAMING_EXCEPTION_H*/
