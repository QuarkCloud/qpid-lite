
//
// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
// 
//   http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.
//

// This source file was created by a code generator.
// Please do not edit.

#include "qpid/broker/manage/Package.h"
#include "qpid/broker/manage/System.h"
#include "qpid/broker/manage/Memory.h"
#include "qpid/broker/manage/Broker.h"
#include "qpid/broker/manage/Agent.h"
#include "qpid/broker/manage/Vhost.h"
#include "qpid/broker/manage/Queue.h"
#include "qpid/broker/manage/Exchange.h"
#include "qpid/broker/manage/Binding.h"
#include "qpid/broker/manage/Subscription.h"
#include "qpid/broker/manage/Connection.h"
#include "qpid/broker/manage/Incoming.h"
#include "qpid/broker/manage/Outgoing.h"
#include "qpid/broker/manage/Domain.h"
#include "qpid/broker/manage/Topic.h"
#include "qpid/broker/manage/QueuePolicy.h"
#include "qpid/broker/manage/TopicPolicy.h"
#include "qpid/broker/manage/Link.h"
#include "qpid/broker/manage/Bridge.h"
#include "qpid/broker/manage/Session.h"
#include "qpid/broker/manage/ManagementSetupState.h"
#include "qpid/broker/manage/EventClientConnect.h"
#include "qpid/broker/manage/EventClientConnectFail.h"
#include "qpid/broker/manage/EventClientDisconnect.h"
#include "qpid/broker/manage/EventBrokerLinkUp.h"
#include "qpid/broker/manage/EventBrokerLinkDown.h"
#include "qpid/broker/manage/EventQueueDeclare.h"
#include "qpid/broker/manage/EventQueueDelete.h"
#include "qpid/broker/manage/EventExchangeDeclare.h"
#include "qpid/broker/manage/EventExchangeDelete.h"
#include "qpid/broker/manage/EventBind.h"
#include "qpid/broker/manage/EventUnbind.h"
#include "qpid/broker/manage/EventSubscribe.h"
#include "qpid/broker/manage/EventUnsubscribe.h"
#include "qpid/broker/manage/EventQueueThresholdCrossedUpward.h"
#include "qpid/broker/manage/EventQueueThresholdCrossedDownward.h"
#include "qpid/broker/manage/EventQueueRedirect.h"
#include "qpid/broker/manage/EventQueueRedirectCancelled.h"
#include "qpid/broker/manage/EventQueueThresholdExceeded.h"


namespace qpid {
	namespace broker {
		namespace manage {

			Package::Package(::qpid::broker::ManagementAgent* agent)
			{
				System::registerSelf(agent);
				Memory::registerSelf(agent);
				Broker::registerSelf(agent);
				Agent::registerSelf(agent);
				Vhost::registerSelf(agent);
				Queue::registerSelf(agent);
				Exchange::registerSelf(agent);
				Binding::registerSelf(agent);
				Subscription::registerSelf(agent);
				Connection::registerSelf(agent);
				Incoming::registerSelf(agent);
				Outgoing::registerSelf(agent);
				Domain::registerSelf(agent);
				Topic::registerSelf(agent);
				QueuePolicy::registerSelf(agent);
				TopicPolicy::registerSelf(agent);
				Link::registerSelf(agent);
				Bridge::registerSelf(agent);
				Session::registerSelf(agent);
				ManagementSetupState::registerSelf(agent);
				EventClientConnect::registerSelf(agent);
				EventClientConnectFail::registerSelf(agent);
				EventClientDisconnect::registerSelf(agent);
				EventBrokerLinkUp::registerSelf(agent);
				EventBrokerLinkDown::registerSelf(agent);
				EventQueueDeclare::registerSelf(agent);
				EventQueueDelete::registerSelf(agent);
				EventExchangeDeclare::registerSelf(agent);
				EventExchangeDelete::registerSelf(agent);
				EventBind::registerSelf(agent);
				EventUnbind::registerSelf(agent);
				EventSubscribe::registerSelf(agent);
				EventUnsubscribe::registerSelf(agent);
				EventQueueThresholdCrossedUpward::registerSelf(agent);
				EventQueueThresholdCrossedDownward::registerSelf(agent);
				EventQueueRedirect::registerSelf(agent);
				EventQueueRedirectCancelled::registerSelf(agent);
				EventQueueThresholdExceeded::registerSelf(agent);
			}
		}
	}
}

