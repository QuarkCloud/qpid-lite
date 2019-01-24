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
#include "qpid/amqp/Sender.h"
#include "qpid/amqp/Address.h"
#include "qpid/amqp/Message.h"
#include "qpid/amqp/SenderImpl.h"
#include "qpid/amqp/Session.h"
#include "qpid/amqp/PrivateImplRef.h"

namespace qpid {
	namespace amqp {

		// Explicitly instantiate Handle superclass
		template class Handle<SenderImpl>;

		typedef PrivateImplRef<qpid::amqp::Sender> PI;

		Sender::Sender(SenderImpl* impl) { PI::ctor(*this, impl); }
		Sender::Sender(const Sender& s) : qpid::amqp::Handle<SenderImpl>() { PI::copy(*this, s); }
		Sender::~Sender() { PI::dtor(*this); }
		Sender& Sender::operator=(const Sender& s) { return PI::assign(*this, s); }
		void Sender::send(const Message& message, bool sync) { impl->send(message, sync); }
		void Sender::close() { impl->close(); }
		void Sender::setCapacity(uint32_t c) { impl->setCapacity(c); }
		uint32_t Sender::getCapacity() { return impl->getCapacity(); }
		uint32_t Sender::getUnsettled() { return impl->getUnsettled(); }
		uint32_t Sender::getAvailable() { return getCapacity() - getUnsettled(); }
		const std::string& Sender::getName() const { return impl->getName(); }
		Session Sender::getSession() const { return impl->getSession(); }
		Address Sender::getAddress() const { return impl->getAddress(); }
	}
}// namespace qpid::amqp
