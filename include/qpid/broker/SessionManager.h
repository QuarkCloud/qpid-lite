#ifndef QPID_BROKER_SESSION_MANAGER_H
#define QPID_BROKER_SESSION_MANAGER_H 1

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

#include <qpid/broker/SessionState.h>
#include <qpid/broker/SessionHandler.h>
#include <qpid/base/SessionId.h>
#include <qpid/sys/Time.h>
#include <qpid/sys/Mutex.h>
#include <qpid/sys/RefCounted.h>

#include <set>
#include <vector>
#include <memory>

#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/intrusive_ptr.hpp>

namespace qpid {
	namespace broker {

		/**
		 * Create and manage SessionState objects.
		 */
		class SessionManager : private boost::noncopyable {
		public:
			SessionManager(const qpid::broker::SessionState::Configuration&, Broker&);

			~SessionManager();

			/** Open a new active session, caller takes ownership */
			std::auto_ptr<qpid::broker::SessionState> attach(SessionHandler& h, const qpid::base::SessionId& id, bool/*force*/);

			/** Return a detached session to the manager, start the timeout counter. */
			void detach(std::auto_ptr<qpid::broker::SessionState>);

			/** Forget about an attached session. Called by SessionState destructor. */
			void forget(const qpid::base::SessionId&);

			Broker& getBroker() const { return broker; }

			const qpid::base::SessionState::Configuration& getSessionConfig() const { return config; }

		private:
			typedef boost::ptr_vector<qpid::broker::SessionState> Detached; // Sorted in expiry order.
			typedef std::set<qpid::base::SessionId> Attached;

			void eraseExpired();

			sys::Mutex lock;
			Detached detached;
			Attached attached;
			qpid::broker::SessionState::Configuration config;
			Broker& broker;
		};
	}
}// namespace qpid::broker

#endif  /*!QPID_BROKER_SESSION_MANAGER_H*/
