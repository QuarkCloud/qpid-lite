#ifndef QPID_AMQP_RECEIVER_IMPL_H
#define QPID_AMQP_RECEIVER_IMPL_H 1

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
#include "qpid/sys/RefCounted.h"
#include "qpid/sys/IntegerTypes.h"
#include "qpid/sys/Time.h"

namespace qpid {
	namespace amqp {

		class Address;
		class Message;
		class MessageListener;
		class Session;

		class ReceiverImpl : public virtual qpid::sys::RefCounted
		{
		public:
			virtual ~ReceiverImpl() {}
			virtual bool get(Message& message, sys::MilliDuration timeout) = 0;
			virtual Message get(sys::MilliDuration timeout) = 0;
			virtual bool fetch(Message& message, sys::MilliDuration timeout) = 0;
			virtual Message fetch(sys::MilliDuration timeout) = 0;
			virtual void setCapacity(uint32_t) = 0;
			virtual uint32_t getCapacity() = 0;
			virtual uint32_t getAvailable() = 0;
			virtual uint32_t getUnsettled() = 0;
			virtual void close() = 0;
			virtual const std::string& getName() const = 0;
			virtual Session getSession() const = 0;
			virtual bool isClosed() const = 0;
			virtual Address getAddress() const = 0;
		};
	}
}// namespace qpid::amqp

#endif  /*!QPID_AMQP_RECEIVER_IMPL_H*/
