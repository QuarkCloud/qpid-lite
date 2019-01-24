#ifndef QPID_AMQP_DRIVER_IMPL_H
#define QPID_AMQP_DRIVER_IMPL_H 1

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
#include "qpid/sys/Mutex.h"
#include "qpid/sys/Thread.h"
#include "qpid/sys/Poller.h"
#include "qpid/sys/Timer.h"
#include "qpid/sys/TransportContext.h"
#include "qpid/sys/Transport.h"

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace qpid {
	namespace amqp {
		using sys::TransportContext;
		using sys::Transport;

		/**
		 *
		 */
		class DriverImpl
		{
		public:
			DriverImpl();
			~DriverImpl();

			QPID_AMQP_EXTERN void start();
			QPID_AMQP_EXTERN void stop();

			QPID_AMQP_EXTERN boost::shared_ptr<Transport> getTransport(const std::string& protocol, TransportContext& connection);
			QPID_AMQP_EXTERN sys::Timer& getTimer() { return *timer; }

			QPID_AMQP_EXTERN static boost::shared_ptr<DriverImpl> getDefault();
		private:
			boost::shared_ptr<qpid::sys::Poller> poller;
			qpid::sys::Thread thread;
			std::auto_ptr<sys::Timer> timer;

			static qpid::sys::Mutex defaultLock;
			static boost::weak_ptr<DriverImpl> theDefault;
		};
	}
}// namespace qpid::amqp

#endif  /*!QPID_AMQP_DRIVER_IMPL_H*/
