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
#include "qpid/amqp/Session.h"
#include "qpid/amqp/Address.h"
#include "qpid/amqp/Connection.h"
#include "qpid/amqp/Message.h"
#include "qpid/amqp/Sender.h"
#include "qpid/amqp/Receiver.h"
#include "qpid/amqp/SessionImpl.h"
#include "qpid/amqp/PrivateImplRef.h"

namespace qpid {
	namespace amqp {

		//  Explicitly instantiate Handle superclass
		template class Handle<SessionImpl>;

		typedef PrivateImplRef<qpid::amqp::Session> PI;

		Session::Session(SessionImpl* impl) { PI::ctor(*this, impl); }
		Session::Session(const Session& s) : Handle<SessionImpl>() { PI::copy(*this, s); }
		Session::~Session() { PI::dtor(*this); }
		Session& Session::operator=(const Session& s) { return PI::assign(*this, s); }
		void Session::commit() { impl->commit(); }
		void Session::rollback() { impl->rollback(); }
		void Session::acknowledge(bool sync) { impl->acknowledge(sync); }
		void Session::acknowledge(Message& m, bool s) { impl->acknowledge(m, false); sync(s); }
		void Session::acknowledgeUpTo(Message& m, bool s) { impl->acknowledge(m, true); sync(s); }
		void Session::reject(Message& m) { impl->reject(m); }
		void Session::release(Message& m) { impl->release(m); }
		void Session::close() { impl->close(); }

		Sender Session::createSender(const Address& address)
		{
			return impl->createSender(address);
		}
		Receiver Session::createReceiver(const Address& address)
		{
			return impl->createReceiver(address);
		}

		Sender Session::createSender(const std::string& address)
		{
			return impl->createSender(Address(address));
		}
		Receiver Session::createReceiver(const std::string& address)
		{
			return impl->createReceiver(Address(address));
		}

		void Session::sync(bool block)
		{
			impl->sync(block);
		}

		bool Session::nextReceiver(Receiver& receiver, sys::MilliDuration timeout)
		{
			return impl->nextReceiver(receiver, timeout);
		}


		Receiver Session::nextReceiver(sys::MilliDuration timeout)
		{
			return impl->nextReceiver(timeout);
		}

		uint32_t Session::getReceivable() { return impl->getReceivable(); }
		uint32_t Session::getUnsettledAcks() { return impl->getUnsettledAcks(); }

		Sender Session::getSender(const std::string& name) const
		{
			return impl->getSender(name);
		}
		Receiver Session::getReceiver(const std::string& name) const
		{
			return impl->getReceiver(name);
		}

		Connection Session::getConnection() const
		{
			return impl->getConnection();
		}

		void Session::checkError() { impl->checkError(); }
		bool Session::hasError()
		{
			try {
				checkError();
				return false;
			}
			catch (const std::exception&) {
				return true;
			}
		}
	}
}// namespace qpid::amqpamqp
