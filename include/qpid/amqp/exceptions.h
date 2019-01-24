#ifndef QPID_AMQP_EXCEPTIONS_H
#define QPID_AMQP_EXCEPTIONS_H 1

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
#include "qpid/types/Exception.h"
#include "qpid/types/Variant.h"

namespace qpid {
namespace amqp {

/** \ingroup messaging
 */

/**
 * This is the base class for all messaging related exceptions thrown
 * by this API.
 */
struct QPID_AMQP_CLASS_EXTERN MessagingException : public qpid::types::Exception
{
    QPID_AMQP_EXTERN MessagingException(const std::string& msg);
    QPID_AMQP_EXTERN virtual ~MessagingException() throw();
};

/**
 * Thrown when the syntax of the option string used to configure a
 * connection in not valid
 */
struct QPID_AMQP_CLASS_EXTERN InvalidOptionString : public MessagingException
{
    QPID_AMQP_EXTERN InvalidOptionString(const std::string& msg);
};

/**
 * Thrown to indicate a failed lookup of some local object. For
 * example when attempting to retrieve a session, sender or receiver
 * by name.
 */
struct QPID_AMQP_CLASS_EXTERN KeyError : public MessagingException
{
    QPID_AMQP_EXTERN KeyError(const std::string&);
};

struct QPID_AMQP_CLASS_EXTERN LinkError : public MessagingException
{
    QPID_AMQP_EXTERN LinkError(const std::string&);
};

struct QPID_AMQP_CLASS_EXTERN AddressError : public LinkError
{
    QPID_AMQP_EXTERN AddressError(const std::string&);
};

/**
 * Thrown when a syntactically correct address cannot be resolved or
 * used.
 */
struct QPID_AMQP_CLASS_EXTERN ResolutionError : public AddressError
{
    QPID_AMQP_EXTERN ResolutionError(const std::string& msg);
};

/**
 * Thrown when creating a sender or receiver for an address for which
 * some asserted property of the node is not matched.
 */
struct QPID_AMQP_CLASS_EXTERN AssertionFailed : public ResolutionError
{
    QPID_AMQP_EXTERN AssertionFailed(const std::string& msg);
};

/**
 * Thrown on attempts to create a sender or receiver to a non-existent
 * node.
 */
struct QPID_AMQP_CLASS_EXTERN NotFound : public ResolutionError
{
    QPID_AMQP_EXTERN NotFound(const std::string& msg);
};

/**
 * Thrown when an address string with invalid syntax is used.
 */
struct QPID_AMQP_CLASS_EXTERN MalformedAddress : public AddressError
{
    QPID_AMQP_EXTERN MalformedAddress(const std::string& msg);
};

struct QPID_AMQP_CLASS_EXTERN ReceiverError : public LinkError
{
    QPID_AMQP_EXTERN ReceiverError(const std::string&);
};

struct QPID_AMQP_CLASS_EXTERN FetchError : public ReceiverError
{
    QPID_AMQP_EXTERN FetchError(const std::string&);
};

/**
 * Thrown by Receiver::fetch(), Receiver::get() and
 * Session::nextReceiver() to indicate that there no message was
 * available before the timeout specified.
 */
struct QPID_AMQP_CLASS_EXTERN NoMessageAvailable : public FetchError
{
    QPID_AMQP_EXTERN NoMessageAvailable();
};

struct QPID_AMQP_CLASS_EXTERN SenderError : public LinkError
{
    QPID_AMQP_EXTERN SenderError(const std::string&);
};

struct QPID_AMQP_CLASS_EXTERN SendError : public SenderError
{
    QPID_AMQP_EXTERN SendError(const std::string&);
};

/**
 * Thrown on a synchronous send to indicate that the message being
 * sent was rejected.
 */
struct QPID_AMQP_CLASS_EXTERN MessageRejected : public SendError
{
    QPID_AMQP_EXTERN MessageRejected(const std::string&);
};

/**
 * Thrown to indicate that the sender attempted to send a message that
 * would result in the target node on the peer exceeding a
 * preconfigured capacity.
 */
struct QPID_AMQP_CLASS_EXTERN TargetCapacityExceeded : public SendError
{
    QPID_AMQP_EXTERN TargetCapacityExceeded(const std::string&);
};

/**
 * Thrown to indicate that the locally configured sender capacity has
 * been reached, and thus no further messages can be put on the replay
 * buffer.
 */
struct QPID_AMQP_CLASS_EXTERN OutOfCapacity : public SendError
{
    QPID_AMQP_EXTERN OutOfCapacity(const std::string&);
};

struct QPID_AMQP_CLASS_EXTERN SessionError : public MessagingException
{
    QPID_AMQP_EXTERN SessionError(const std::string&);
};

/**
 * Thrown to indicate that the sesion was closed by this client (probably in
 * a different thread) whilst we were waiting on it. This is not really an
 * error condition but there is no other way to return this.
 */
struct QPID_AMQP_CLASS_EXTERN SessionClosed : public SessionError
{
  QPID_AMQP_EXTERN SessionClosed();
};

/** Base class for transactional errors */
struct QPID_AMQP_CLASS_EXTERN TransactionError : public SessionError
{
    QPID_AMQP_EXTERN TransactionError(const std::string&);
};

/**
 * The transaction was automatically rolled back.  This could be due to an error
 * on the broker, such as a store failure, or a connection failure during the
 * transaction
 */
struct QPID_AMQP_CLASS_EXTERN TransactionAborted : public TransactionError
{
    QPID_AMQP_EXTERN TransactionAborted(const std::string&);
};

/**
 * The outcome of the transaction on the broker, commit or roll-back, is not
 * known. This occurs when the connection fails after we sent the commit but
 * before we received a result.
 */
struct QPID_AMQP_CLASS_EXTERN TransactionUnknown : public TransactionError
{
    QPID_AMQP_EXTERN TransactionUnknown(const std::string&);
};

/**
 * Thrown to indicate that the application attempted to do something
 * for which it was not authorised by its peer.
 */
struct QPID_AMQP_CLASS_EXTERN UnauthorizedAccess : public SessionError
{
    QPID_AMQP_EXTERN UnauthorizedAccess(const std::string&);
};

struct QPID_AMQP_CLASS_EXTERN ConnectionError : public MessagingException
{
    QPID_AMQP_EXTERN ConnectionError(const std::string&);
};

struct QPID_AMQP_CLASS_EXTERN ProtocolVersionError : public ConnectionError
{
    QPID_AMQP_EXTERN ProtocolVersionError(const std::string&);
};

struct QPID_AMQP_CLASS_EXTERN AuthenticationFailure : public ConnectionError
{
    QPID_AMQP_EXTERN AuthenticationFailure(const std::string&);
};

/**
 * Thrown to indicate loss of underlying connection. When
 * auto-reconnect is used this will be caught by the library and used
 * to trigger reconnection attempts. If reconnection fails (according
 * to whatever settings have been configured), then an instnace of
 * this class will be thrown to signal that.
 */
struct QPID_AMQP_CLASS_EXTERN TransportFailure : public MessagingException
{
    QPID_AMQP_EXTERN TransportFailure(const std::string&);
};

}} // namespace qpid::amqp

#endif  /*!QPID_AMQP_EXCEPTIONS_H*/
