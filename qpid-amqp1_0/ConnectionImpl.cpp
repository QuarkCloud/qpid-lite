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
#include "qpid/amqp1_0/ConnectionImpl.h"
#include "qpid/amqp1_0/ConnectionContext.h"
#include "qpid/amqp1_0/SessionImpl.h"

#include "qpid/amqp/DriverImpl.h"
#include "qpid/amqp/ConnectionImpl.h"
#include "qpid/amqp/Session.h"
#include "qpid/amqp/ProtocolRegistry.h"

#include "qpid/sys/Exception.h"

namespace qpid {
	namespace amqp1_0 {
		// Static constructor which registers this implementation in the ProtocolRegistry
		namespace {
			amqp::ConnectionImpl* create(const std::string& u, const qpid::types::Variant::Map& o)
			{
				try {
					return new ConnectionImpl(u, o);
				}
				catch (const types::Exception&) {
					throw;
				}
				catch (const qpid::sys::Exception& e) {
					throw amqp::ConnectionError(e.what());
				}
			}

			void shutdown() {
				amqp::DriverImpl::getDefault()->stop();
			}

			struct StaticInit
			{
				StaticInit()
				{
					amqp::ProtocolRegistry::add("amqp1.0", &create, &shutdown);
				};
			} init;
		}

		ConnectionImpl::ConnectionImpl(const std::string& url, const qpid::types::Variant::Map& options) :
			connection(new ConnectionContext(url, options)) 
		{
		}

		ConnectionImpl::ConnectionImpl(boost::shared_ptr<ConnectionContext> c) : connection(c) 
		{
		}

		void ConnectionImpl::open()
		{
			connection->open();
		}

		bool ConnectionImpl::isOpen() const
		{
			return connection->isOpen();
		}

		void ConnectionImpl::close()
		{
			connection->close();
		}

		amqp::Session ConnectionImpl::newSession(bool transactional, const std::string& name)
		{
			return qpid::amqp::Session(new SessionImpl(connection, connection->newSession(transactional, name)));
		}

		amqp::Session ConnectionImpl::getSession(const std::string& name) const
		{
			return qpid::amqp::Session(new SessionImpl(connection, connection->getSession(name)));
		}

		void ConnectionImpl::setOption(const std::string& name, const qpid::types::Variant& value)
		{
			connection->setOption(name, value);
		}

		std::string ConnectionImpl::getAuthenticatedUsername()
		{
			return connection->getAuthenticatedUsername();
		}

		void ConnectionImpl::reconnect(const std::string& url)
		{
			connection->reconnect(url);
		}
		void ConnectionImpl::reconnect()
		{
			connection->reconnect();
		}
		std::string ConnectionImpl::getUrl() const
		{
			return connection->getUrl();
		}

	}
}// namespace qpid::amqp
