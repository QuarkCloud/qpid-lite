#ifndef QPID_AMQP_RECEIVER_H
#define QPID_AMQP_RECEIVER_H 1

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
#include "qpid/sys/Time.h"

namespace qpid {
	namespace amqp {

		template <class> class PrivateImplRef;

		class Address;
		class Message;
		class ReceiverImpl;
		class Session;

		/**   \ingroup messaging
		 * Interface through which messages are received.
		 */
		class QPID_AMQP_CLASS_EXTERN Receiver : public qpid::amqp::Handle<ReceiverImpl>
		{
		public:
			QPID_AMQP_EXTERN Receiver(ReceiverImpl* impl = 0);
			QPID_AMQP_EXTERN Receiver(const Receiver&);
			QPID_AMQP_EXTERN ~Receiver();
			QPID_AMQP_EXTERN Receiver& operator=(const Receiver&);
			/**
			 * Retrieves a message from this Receiver's local queue or waits
			 * for up to the specified timeout for a message to become
			 * available.
			 */
			QPID_AMQP_EXTERN bool get(Message& message, sys::MilliDuration timeout = sys::MilliDuration::FOREVER);
			/**
			 * Retrieves a message from this Receiver's local queue or waits
			 * for up to the specified timeout for a message to become
			 * available.
			 *
			 * @exception NoMessageAvailable if there is no message to give
			 * after waiting for the specified timeout, or if the Receiver is
			 * closed, in which case isClosed() will be true.
			 */
			QPID_AMQP_EXTERN Message get(sys::MilliDuration timeout = sys::MilliDuration::FOREVER);
			/**
			 * Retrieves a message from this Receiver's subscription or waits
			 * for up to the specified timeout for one to become
			 * available. Unlike get(), this method will check with the server
			 * that there is no message for the subscription this receiver is
			 * serving before returning false.
			 *
			 * @return false if there is no message available after
			 * waiting for the specified time period, or if the receiver is
			 * closed, in which case isClosed() will be true.
			 */
			QPID_AMQP_EXTERN bool fetch(Message& message, sys::MilliDuration timeout = sys::MilliDuration::FOREVER);
			/**
			 * Retrieves a message for this Receiver's subscription or waits
			 * for up to the specified timeout for one to become
			 * available. Unlike get(), this method will check with the server
			 * that there is no message for the subscription this receiver is
			 * serving before throwing an exception.
			 *
			 * @exception NoMessageAvailable if there is no message available
			 * after waiting for the specified timeout, or if the Receiver is
			 * closed, in which case isClose() will be true.
			 */
			QPID_AMQP_EXTERN Message fetch(sys::MilliDuration timeout = sys::MilliDuration::FOREVER);
			/**
			 * Sets the capacity for the Receiver. The capacity determines how
			 * many incoming messages can be held in the Receiver before being
			 * requested by a client via fetch() (or pushed to a listener).
			 */
			QPID_AMQP_EXTERN void setCapacity(uint32_t);
			/**
			 * @return the capacity of the Receiver. The capacity determines
			 * how many incoming messages can be held in the Receiver before
			 * being requested by a client via fetch() (or pushed to a
			 * listener).
			 */
			QPID_AMQP_EXTERN uint32_t getCapacity();
			/**
			 * @return the number of messages received and waiting to be
			 * fetched.
			 */
			QPID_AMQP_EXTERN uint32_t getAvailable();
			/**
			 * @return the number of messages received on this
			 * Receiver that have been acknowledged, but for which that
			 * acknowledgement has not yet been confirmed as processed by the
			 * server.
			 */
			QPID_AMQP_EXTERN uint32_t getUnsettled();

			/**
			 * Cancels this Receiver.
			 */
			QPID_AMQP_EXTERN void close();

			/**
			 * Return true if the Receiver was closed by a call to close().
			 */
			QPID_AMQP_EXTERN bool isClosed() const;

			/**
			 * Returns the name of this Receiver.
			 */
			QPID_AMQP_EXTERN const std::string& getName() const;

			/**
			 * Returns a handle to the session associated with this Receiver.
			 */
			QPID_AMQP_EXTERN Session getSession() const;

			/**
			 * Returns an address for this Receiver.
			 */
			QPID_AMQP_EXTERN Address getAddress() const;


		private:
			friend class qpid::amqp::PrivateImplRef<Receiver>;
		};
	}
}// namespace qpid::amqp

#endif  /*!QPID_AMQP_RECEIVER_H*/
