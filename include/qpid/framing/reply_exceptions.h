#ifndef QPID_FRAMING_REPLY_EXCEPTIONS_H
#define QPID_FRAMING_REPLY_EXCEPTIONS_H 1
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

///
/// This file was automatically generated from the AMQP specification.
/// Do not edit.
///


#include "qpid/sys/Exception.h"
#include "qpid/framing/Exception.h"
#include "qpid/sys/ExceptionHolder.h"
#include "qpid/framing/enum.h"
#include "qpid/framing/Compile.h"

namespace qpid {
namespace framing {


struct UnauthorizedAccessException:
    SessionException
{
    std::string getPrefix() const { return "unauthorized-access"; }
    UnauthorizedAccessException(const std::string& msg=std::string()) : SessionException(execution::ERROR_CODE_UNAUTHORIZED_ACCESS, ""+msg) {}
};

struct NotFoundException:
    SessionException
{
    std::string getPrefix() const { return "not-found"; }
    NotFoundException(const std::string& msg=std::string()) : SessionException(execution::ERROR_CODE_NOT_FOUND, ""+msg) {}
};

struct ResourceLockedException:
    SessionException
{
    std::string getPrefix() const { return "resource-locked"; }
    ResourceLockedException(const std::string& msg=std::string()) : SessionException(execution::ERROR_CODE_RESOURCE_LOCKED, ""+msg) {}
};

struct PreconditionFailedException:
    SessionException
{
    std::string getPrefix() const { return "precondition-failed"; }
    PreconditionFailedException(const std::string& msg=std::string()) : SessionException(execution::ERROR_CODE_PRECONDITION_FAILED, ""+msg) {}
};

struct ResourceDeletedException:
    SessionException
{
    std::string getPrefix() const { return "resource-deleted"; }
    ResourceDeletedException(const std::string& msg=std::string()) : SessionException(execution::ERROR_CODE_RESOURCE_DELETED, ""+msg) {}
};

struct IllegalStateException:
    SessionException
{
    std::string getPrefix() const { return "illegal-state"; }
    IllegalStateException(const std::string& msg=std::string()) : SessionException(execution::ERROR_CODE_ILLEGAL_STATE, ""+msg) {}
};

struct CommandInvalidException:
    SessionException
{
    std::string getPrefix() const { return "command-invalid"; }
    CommandInvalidException(const std::string& msg=std::string()) : SessionException(execution::ERROR_CODE_COMMAND_INVALID, ""+msg) {}
};

struct ResourceLimitExceededException:
    SessionException
{
    std::string getPrefix() const { return "resource-limit-exceeded"; }
    ResourceLimitExceededException(const std::string& msg=std::string()) : SessionException(execution::ERROR_CODE_RESOURCE_LIMIT_EXCEEDED, ""+msg) {}
};

struct NotAllowedException:
    SessionException
{
    std::string getPrefix() const { return "not-allowed"; }
    NotAllowedException(const std::string& msg=std::string()) : SessionException(execution::ERROR_CODE_NOT_ALLOWED, ""+msg) {}
};

struct IllegalArgumentException:
    SessionException
{
    std::string getPrefix() const { return "illegal-argument"; }
    IllegalArgumentException(const std::string& msg=std::string()) : SessionException(execution::ERROR_CODE_ILLEGAL_ARGUMENT, ""+msg) {}
};

struct NotImplementedException:
    SessionException
{
    std::string getPrefix() const { return "not-implemented"; }
    NotImplementedException(const std::string& msg=std::string()) : SessionException(execution::ERROR_CODE_NOT_IMPLEMENTED, ""+msg) {}
};

struct InternalErrorException:
    SessionException
{
    std::string getPrefix() const { return "internal-error"; }
    InternalErrorException(const std::string& msg=std::string()) : SessionException(execution::ERROR_CODE_INTERNAL_ERROR, ""+msg) {}
};

struct InvalidArgumentException:
    SessionException
{
    std::string getPrefix() const { return "invalid-argument"; }
    InvalidArgumentException(const std::string& msg=std::string()) : SessionException(execution::ERROR_CODE_INVALID_ARGUMENT, ""+msg) {}
};

QPID_FRAMING_EXTERN sys::ExceptionHolder createSessionException(int code, const std::string& text);

struct ConnectionForcedException:
    ConnectionException
{
    std::string getPrefix() const { return "connection-forced"; }
    ConnectionForcedException(const std::string& msg=std::string()) : ConnectionException(connection::CLOSE_CODE_CONNECTION_FORCED, ""+msg) {}
};

struct InvalidPathException:
    ConnectionException
{
    std::string getPrefix() const { return "invalid-path"; }
    InvalidPathException(const std::string& msg=std::string()) : ConnectionException(connection::CLOSE_CODE_INVALID_PATH, ""+msg) {}
};

struct FramingErrorException:
    ConnectionException
{
    std::string getPrefix() const { return "framing-error"; }
    FramingErrorException(const std::string& msg=std::string()) : ConnectionException(connection::CLOSE_CODE_FRAMING_ERROR, ""+msg) {}
};

QPID_FRAMING_EXTERN sys::ExceptionHolder createConnectionException(int code, const std::string& text);

struct SessionBusyException:
    ChannelException
{
    std::string getPrefix() const { return "session-busy"; }
    SessionBusyException(const std::string& msg=std::string()) : ChannelException(session::DETACH_CODE_SESSION_BUSY, ""+msg) {}
};

struct TransportBusyException:
    ChannelException
{
    std::string getPrefix() const { return "transport-busy"; }
    TransportBusyException(const std::string& msg=std::string()) : ChannelException(session::DETACH_CODE_TRANSPORT_BUSY, ""+msg) {}
};

struct NotAttachedException:
    ChannelException
{
    std::string getPrefix() const { return "not-attached"; }
    NotAttachedException(const std::string& msg=std::string()) : ChannelException(session::DETACH_CODE_NOT_ATTACHED, ""+msg) {}
};

struct UnknownIdsException:
    ChannelException
{
    std::string getPrefix() const { return "unknown-ids"; }
    UnknownIdsException(const std::string& msg=std::string()) : ChannelException(session::DETACH_CODE_UNKNOWN_IDS, ""+msg) {}
};

QPID_FRAMING_EXTERN sys::ExceptionHolder createChannelException(int code, const std::string& text);

}} // namespace qpid::framing

#endif  /*!QPID_FRAMING_REPLY_EXCEPTIONS_H*/
