#ifndef QPID_AMQP0_10_CONNECTION_IMPL_H
#define QPID_AMQP0_10_CONNECTION_IMPL_H 1

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
#include "qpid/driver/Connection.h"
#include "qpid/amqp/ConnectionOptions.h"
#include "qpid/amqp/ConnectionImpl.h"
#include "qpid/types/Variant.h"
#include "qpid/sys/Mutex.h"
#include "qpid/sys/Semaphore.h"
#include "qpid/sys/Url.h"
#include <map>
#include <vector>

namespace qpid {
	namespace amqp0_10 {

		class SessionImpl;

		class ConnectionImpl : public qpid::amqp::ConnectionImpl
		{
		public:
			ConnectionImpl(const std::string& url, const qpid::types::Variant::Map& options);
			void open();
			void reopen();
			bool isOpen() const;
			void close();
			qpid::amqp::Session newSession(bool transactional, const std::string& name);
			qpid::amqp::Session getSession(const std::string& name) const;
			void closed(SessionImpl&);
			void detach();
			void setOption(const std::string& name, const qpid::types::Variant& value);
			bool backoff();
			std::string getAuthenticatedUsername();
			void reconnect(const std::string& url);
			void reconnect();
			std::string getUrl() const;
			bool getAutoDecode() const;
			bool getAutoReconnect() const;
		private:
			typedef std::map<std::string, qpid::amqp::Session> Sessions;

			mutable qpid::sys::Mutex lock;//used to protect data structures
			qpid::sys::Semaphore semaphore;//used to coordinate reconnection
			Sessions sessions;
			qpid::driver::Connection connection;
			bool replaceUrls;     // Replace rather than merging with reconnect-urls
			std::vector<std::string> urls;
			qpid::amqp::ConnectionOptions settings;
			bool autoReconnect;
			double timeout;
			int32_t limit;
			double minReconnectInterval;
			double maxReconnectInterval;
			int32_t retries;
			bool reconnectOnLimitExceeded;
			bool disableAutoDecode;

			void setOptions(const qpid::types::Variant::Map& options);
			void connect(const qpid::sys::AbsTime& started);
			bool tryConnect();
			bool resetSessions(const sys::Mutex::ScopedLock&); // dummy parameter indicates call with lock held.
			void mergeUrls(const std::vector<sys::Url>& more, const sys::Mutex::ScopedLock&);
		};
	}
}// namespace qpid::amqp0_10

#endif  /*!QPID_AMQP0_10_CONNECTION_IMPL_H*/
