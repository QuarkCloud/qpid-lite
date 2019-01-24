#ifndef QPID_AMQP1_0_CONNECTION_IMPL_H
#define QPID_AMQP1_0_CONNECTION_IMPL_H 1

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
#include <boost/shared_ptr.hpp>
#include "qpid/amqp/ConnectionImpl.h"
#include "qpid/amqp/Session.h"
#include "qpid/types/Variant.h"

namespace qpid {
	namespace amqp1_0 {

		class ConnectionContext;
		/**
		 * Handles are directly referenced by applications; Contexts are
		 * referenced by Handles. This allows a graph structure that
		 * remains intact as long as the application references any part
		 * of it, but that can be automatically reclaimed if the whole
		 * graph becomes unreferenced.
		 */
		class ConnectionImpl : public qpid::amqp::ConnectionImpl
		{
		public:
			ConnectionImpl(const std::string& url, const qpid::types::Variant::Map& options);
			ConnectionImpl(boost::shared_ptr<ConnectionContext>);
			void open();
			bool isOpen() const;
			void close();
			amqp::Session newSession(bool transactional, const std::string& name);
			amqp::Session getSession(const std::string& name) const;
			void setOption(const std::string& name, const qpid::types::Variant& value);
			std::string getAuthenticatedUsername();
			void reconnect(const std::string& url);
			void reconnect();
			std::string getUrl() const;
		private:
			boost::shared_ptr<ConnectionContext> connection;
		};
	}
}// namespace qpid::amqp1_0

#endif  /*!QPID_AMQP1_0_CONNECTION_IMPL_H*/
