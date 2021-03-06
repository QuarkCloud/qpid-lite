#ifndef QPID_AMQP_SESSION_IMPL_H
#define QPID_AMQP_SESSION_IMPL_H 1

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
#include <string>
#include "qpid/sys/Time.h"

namespace qpid {
	namespace amqp {

		class Address;
		class Connection;
		class Message;
		class Sender;
		class Receiver;

		class SessionImpl : public virtual qpid::sys::RefCounted
		{
		public:
			virtual ~SessionImpl() {}
			virtual void commit() = 0;
			virtual void rollback() = 0;
			virtual void acknowledge(bool sync) = 0;
			virtual void acknowledge(Message&, bool cumulative) = 0;
			virtual void reject(Message&) = 0;
			virtual void release(Message&) = 0;
			virtual void close() = 0;
			virtual void sync(bool block) = 0;
			virtual Sender createSender(const Address& address) = 0;
			virtual Receiver createReceiver(const Address& address) = 0;
			virtual bool nextReceiver(Receiver& receiver, sys::MilliDuration timeout) = 0;
			virtual Receiver nextReceiver(sys::MilliDuration timeout) = 0;
			virtual uint32_t getReceivable() = 0;
			virtual uint32_t getUnsettledAcks() = 0;
			virtual Sender getSender(const std::string& name) const = 0;
			virtual Receiver getReceiver(const std::string& name) const = 0;
			virtual Connection getConnection() const = 0;
			virtual void checkError() = 0;
		private:
		};
	}
}// namespace qpid::amqp

#endif  /*!QPID_AMQP_SESSION_IMPL_H*/
