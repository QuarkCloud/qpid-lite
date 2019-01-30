#ifndef QPID_AMQP0_10_INCOMING_MESSAGES_H
#define QPID_AMQP0_10_INCOMING_MESSAGES_H 1

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

#include "qpid/amqp0_10/AcceptTracker.h"
#include "qpid/amqp/Message.h"
#include "qpid/driver/AsyncSession.h"
#include "qpid/framing/SequenceSet.h"
#include "qpid/framing/FrameSet.h"
#include "qpid/sys/BlockingQueue.h"
#include "qpid/sys/Time.h"
#include <string>
#include <boost/shared_ptr.hpp>

namespace qpid {
	namespace amqp0_10 {

		/**
		 * Queue of incoming messages.
		 */
		class IncomingMessages
		{
		public:
			typedef boost::shared_ptr<qpid::framing::FrameSet> FrameSetPtr;
			class MessageTransfer
			{
			public:
				const std::string& getDestination();
				void retrieve(qpid::amqp::Message* message);
			private:
				FrameSetPtr content;
				IncomingMessages& parent;
				bool checkExpired();

				MessageTransfer(FrameSetPtr, IncomingMessages&);
				friend class IncomingMessages;
			};

			struct Handler
			{
				virtual ~Handler() {}
				virtual bool accept(MessageTransfer& transfer) = 0;
				virtual bool expire(MessageTransfer& transfer) = 0;
				virtual bool isClosed() { return false; }
			};

			IncomingMessages();
			void setSession(qpid::driver::AsyncSession session);
			bool get(Handler& handler, qpid::sys::NanoDuration timeout);
			void wakeup();
			bool getNextDestination(std::string& destination, qpid::sys::NanoDuration timeout);
			void accept();
			void accept(qpid::framing::SequenceNumber id, bool cumulative);
			void releaseAll();
			void releasePending(const std::string& destination);

			uint32_t pendingAccept();
			uint32_t pendingAccept(const std::string& destination);

			uint32_t available();
			uint32_t available(const std::string& destination);
		private:
			typedef std::deque<FrameSetPtr> FrameSetQueue;
			enum ProcessState { EMPTY = 0, OK = 1, CLOSED = 2 };

			sys::Monitor lock;
			qpid::driver::AsyncSession session;
			boost::shared_ptr< sys::BlockingQueue<FrameSetPtr> > incoming;
			bool inUse;
			FrameSetQueue received;
			AcceptTracker acceptTracker;

			ProcessState process(Handler*, qpid::sys::NanoDuration);
			bool wait(qpid::sys::NanoDuration);
			bool pop(FrameSetPtr&, qpid::sys::NanoDuration);

			void retrieve(FrameSetPtr, qpid::amqp::Message*);

		};
	}
}// namespace qpid::amqp0_10

#endif  /*!QPID_AMQP0_10_INCOMING_MESSAGES_H*/
