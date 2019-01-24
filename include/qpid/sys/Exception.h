#ifndef QPID_SYS_EXCEPTION_H
#define QPID_SYS_EXCEPTION_H 1

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

#include "qpid/sys/StrError.h"
#include "qpid/sys/Compile.h"
#include <string>
#include <errno.h>

namespace qpid{
	namespace sys {

		struct DisableExceptionLogging
		{
			QPID_SYS_EXTERN DisableExceptionLogging();
			QPID_SYS_EXTERN ~DisableExceptionLogging();
		};

	/**
	 * Base class for Qpid runtime exceptions.
	 */
	class QPID_SYS_CLASS_EXTERN Exception : public std::exception
	{
	public:
		QPID_SYS_EXTERN explicit Exception(const std::string& message = std::string()) throw();
		QPID_SYS_EXTERN virtual ~Exception() throw();
		QPID_SYS_EXTERN virtual const char* what() const throw(); // prefix: message
		QPID_SYS_EXTERN virtual std::string getMessage() const; // Unprefixed message
		QPID_SYS_EXTERN virtual std::string getPrefix() const;  // Prefix

	private:
		std::string message;
		mutable std::string whatStr;
	};

	/** Exception that includes an errno message. */
	struct QPID_SYS_CLASS_EXTERN ErrnoException : public Exception {
		ErrnoException(const std::string& msg, int err) : Exception(msg + ": " + qpid::sys::strError(err)) {}
		ErrnoException(const std::string& msg) : Exception(msg + ": " + qpid::sys::strError(errno)) {}
	};


	struct QPID_SYS_CLASS_EXTERN ClosedException : public Exception {
		QPID_SYS_EXTERN ClosedException(const std::string& msg = std::string());
		QPID_SYS_EXTERN std::string getPrefix() const;
	};

	/**
	 * Exception representing transport failure
	 */

	struct TransportFailure : public sys::Exception {
		TransportFailure(const std::string& msg = std::string()) : Exception(msg) {}
	};

	struct ProtocolVersionError : public TransportFailure {
		ProtocolVersionError(const std::string& msg = std::string()) : TransportFailure(msg) {}
	};

}

} // namespace qpid

#endif  /*!QPID_SYS_EXCEPTION_H*/
