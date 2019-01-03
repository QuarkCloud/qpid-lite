
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

#include "qpid/broker/manage/PackageACL.h"
#include "qpid/broker/manage/Acl.h"
#include "qpid/broker/manage/EventAllow.h"
#include "qpid/broker/manage/EventDeny.h"
#include "qpid/broker/manage/EventConnectionDeny.h"
#include "qpid/broker/manage/EventQueueQuotaDeny.h"
#include "qpid/broker/manage/EventFileLoaded.h"
#include "qpid/broker/manage/EventFileLoadFailed.h"

namespace qpid {
	namespace broker {
		namespace manage {


			PackageACL::PackageACL(::qpid::broker::ManagementAgent* agent)
			{
				Acl::registerSelf(agent);
				EventAllow::registerSelf(agent);
				EventDeny::registerSelf(agent);
				EventConnectionDeny::registerSelf(agent);
				EventQueueQuotaDeny::registerSelf(agent);
				EventFileLoaded::registerSelf(agent);
				EventFileLoadFailed::registerSelf(agent);

			}
		}
	}
}

