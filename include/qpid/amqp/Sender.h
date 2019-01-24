#ifndef QPID_AMQP_SENDER_H
#define QPID_AMQP_SENDER_H 1

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

#include "qpid/amqp/Handle.h"
#include "qpid/sys/IntegerTypes.h"

#include <string>

namespace qpid {
	namespace amqp {

		template <class> class PrivateImplRef;
		class Address;
		class Message;
		class SenderImpl;
		class Session;
		/**   \ingroup messaging
		 * Interface through which messages are sent.
		 */
		class QPID_AMQP_CLASS_EXTERN Sender : public qpid::amqp::Handle<SenderImpl>
		{
		public:
			QPID_AMQP_EXTERN Sender(SenderImpl* impl = 0);
			QPID_AMQP_EXTERN Sender(const Sender&);
			QPID_AMQP_EXTERN ~Sender();
			QPID_AMQP_EXTERN Sender& operator=(const Sender&);

			/**
			 * Sends a message
			 *
			 * @param message the message to send
			 * @param sync if true the call will block until the server
			 * confirms receipt of the messages; if false will only block for
			 * available capacity (i.e. pending == capacity)
			 */
			QPID_AMQP_EXTERN void send(const Message& message, bool sync = false);
			QPID_AMQP_EXTERN void close();

			/**
			 * Sets the capacity for the sender. The capacity determines how
			 * many outgoing messages can be held pending confirmation of
			 * receipt by the broker.
			 */
			QPID_AMQP_EXTERN void setCapacity(uint32_t);
			/**
			 * Returns the capacity of the sender.
			 * @see setCapacity
			 */
			QPID_AMQP_EXTERN uint32_t getCapacity();
			/**
			 * Returns the number of sent messages pending confirmation of
			 * receipt by the broker. (These are the 'in-doubt' messages).
			 */
			QPID_AMQP_EXTERN uint32_t getUnsettled();
			/**
			 * Returns the number of messages for which there is available
			 * capacity.
			 */
			QPID_AMQP_EXTERN uint32_t getAvailable();
			/**
			 * Returns the name of this sender.
			 */
			QPID_AMQP_EXTERN const std::string& getName() const;

			/**
			 * Returns a handle to the session associated with this sender.
			 */
			QPID_AMQP_EXTERN Session getSession() const;

			/**
			 * Returns an address for this sender.
			 */
			QPID_AMQP_EXTERN Address getAddress() const;

		private:
			friend class qpid::amqp::PrivateImplRef<Sender>;
		};
	}
}// namespace qpid::amqp

#endif  /*!QPID_AMQP_SENDER_H*/
