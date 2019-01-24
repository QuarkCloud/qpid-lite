#ifndef QPID_AMQP_SESSION_H
#define QPID_AMQP_SESSION_H 1

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
#include "qpid/amqp/exceptions.h"
#include "qpid/amqp/Handle.h"

#include "qpid/amqp/PrivateImplRef.h"
#include "qpid/amqp/Address.h"
#include "qpid/amqp/Message.h"
#include "qpid/amqp/Sender.h"
#include "qpid/amqp/Receiver.h"
#include "qpid/amqp/SessionImpl.h"
#include "qpid/sys/Time.h"
#include <string>

namespace qpid {
	namespace amqp {


		/** \ingroup messaging
		 * A session represents a distinct 'conversation' which can involve
		 * sending and receiving messages to and from different addresses.
		 */
		class QPID_AMQP_CLASS_EXTERN Session : public qpid::amqp::Handle<SessionImpl>
		{
		public:
			QPID_AMQP_EXTERN Session(SessionImpl* impl = 0);
			QPID_AMQP_EXTERN Session(const Session&);
			QPID_AMQP_EXTERN ~Session();
			QPID_AMQP_EXTERN Session& operator=(const Session&);

			/**
			 * Closes a session and all associated senders and receivers. An
			 * opened session should be closed before the last handle to it
			 * goes out of scope. All a connections sessions can be closed by
			 * a call to Connection::close().
			 */
			QPID_AMQP_EXTERN void close();

			/**
			 * Commits the sessions transaction.
			 *
			 * @exception TransactionAborted if the transaction was rolled back due to an error.
			 * @exception TransactionUnknown if the connection was lost and the transaction outcome is unknown.
			 * forcing an automatic rollback.
			 */
			QPID_AMQP_EXTERN void commit();
			QPID_AMQP_EXTERN void rollback();

			/**
			 * Acknowledges all outstanding messages that have been received
			 * by the application on this session.
			 *
			 * @param sync if true, blocks until the acknowledgement has been
			 * processed by the server
			 */
			QPID_AMQP_EXTERN void acknowledge(bool sync = false);
			/**
			 * Acknowledges the specified message.
			 */
			QPID_AMQP_EXTERN void acknowledge(Message&, bool sync = false);
			/**
			 * Acknowledges all message up to the specified message.
			 */
			QPID_AMQP_EXTERN void acknowledgeUpTo(Message&, bool sync = false);
			/**
			 * Rejects the specified message. The broker does not redeliver a
			 * message that has been rejected. Once a message has been
			 * acknowledged, it can no longer be rejected.
			 */
			QPID_AMQP_EXTERN void reject(Message&);
			/**
			 * Releases the specified message. The broker may redeliver the
			 * message. Once a message has been acknowledged, it can no longer
			 * be released.
			 */
			QPID_AMQP_EXTERN void release(Message&);

			/**
			 * Request synchronisation with the server.
			 *
			 * @param block if true, this call will block until the server
			 * confirms completion of all pending operations; if false the
			 * call will request notification from the server but will return
			 * before receiving it.
			 */
			QPID_AMQP_EXTERN void sync(bool block = true);

			/**
			 * Returns the total number of messages received and waiting to be
			 * fetched by all Receivers belonging to this session. This is the
			 * total number of available messages across all receivers on this
			 * session.
			 */
			QPID_AMQP_EXTERN uint32_t getReceivable();
			/**
			 * Returns a count of the number of messages received this session
			 * that have been acknowledged, but for which that acknowledgement
			 * has not yet been confirmed as processed by the server.
			 */
			QPID_AMQP_EXTERN uint32_t getUnsettledAcks();
			/**
			 * Retrieves the receiver for the next available message. If there
			 * are no available messages at present the call will block for up
			 * to the specified timeout waiting for one to arrive. Returns
			 * true if a message was available at the point of return, in
			 * which case the passed in receiver reference will be set to the
			 * receiver for that message or false if no message was available.
			 */
			QPID_AMQP_EXTERN bool nextReceiver(Receiver&, sys::MilliDuration timeout = sys::MilliDuration::FOREVER);
			/**
			 * Returns the receiver for the next available message. If there
			 * are no available messages at present the call will block for up
			 * to the specified timeout waiting for one to arrive.
			 *
			 * @exception Receiver::NoMessageAvailable if no message became
			 * available in time.
			 */
			QPID_AMQP_EXTERN Receiver nextReceiver(sys::MilliDuration timeout = sys::MilliDuration::FOREVER);

			/**
			 * Create a new sender through which messages can be sent to the
			 * specified address.
			 *
			 * @exception ResolutionError if there is an error in resolving
			 * the address
			 */
			QPID_AMQP_EXTERN Sender createSender(const Address& address);
			/**
			 * Create a new sender through which messages can be sent to the
			 * specified address.
			 *
			 * @exception ResolutionError if there is an error in resolving
			 * the address
			 *
			 * @exception MalformedAddress if the syntax of address is not
			 * valid
			 */
			QPID_AMQP_EXTERN Sender createSender(const std::string& address);

			/**
			 * Create a new receiver through which messages can be received
			 * from the specified address.
			 *
			 * @exception ResolutionError if there is an error in resolving
			 * the address
			 */
			QPID_AMQP_EXTERN Receiver createReceiver(const Address& address);
			/**
			 * Create a new receiver through which messages can be received
			 * from the specified address.
			 *
			 * @exception ResolutionError if there is an error in resolving
			 * the address
			 *
			 * @exception MalformedAddress if the syntax of address is not
			 * valid
			 */
			QPID_AMQP_EXTERN Receiver createReceiver(const std::string& address);

			/**
			 * Returns the sender with the specified name.
			 * @exception KeyError if there is none for that name.
			 */
			QPID_AMQP_EXTERN Sender getSender(const std::string& name) const;
			/**
			 * Returns the receiver with the specified name.
			 * @exception KeyError if there is none for that name.
			 */
			QPID_AMQP_EXTERN Receiver getReceiver(const std::string& name) const;
			/**
			 * Returns a handle to the connection this session is associated
			 * with.
			 */
			QPID_AMQP_EXTERN Connection getConnection() const;

			/**
			 * @returns true if the session has been rendered invalid by some
			 * exception, false if it is valid for use.
			 */
			QPID_AMQP_EXTERN bool hasError();
			/**
			 * If the session has been rendered invalid by some exception,
			 * this method will result in that exception being thrown on
			 * calling this method.
			 */
			QPID_AMQP_EXTERN void checkError();

		private:
			friend class qpid::amqp::PrivateImplRef<Session>;
		};
	}
}// namespace qpid::amqp

#endif  /*!QPID_AMQP_SESSION_H*/
