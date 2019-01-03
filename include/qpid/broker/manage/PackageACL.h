
#ifndef QPID_BROKER_MANAGE_PACKAGE_ACL_H
#define QPID_BROKER_MANAGE_PACKAGE_ACL_H 1

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

#include "qpid/broker/ManagementAgent.h"
#include "qpid/broker/Compile.h"

namespace qpid {
	namespace broker {
		namespace manage {


			class PackageACL
			{
			public:
				QPID_BROKER_EXTERN PackageACL(::qpid::broker::ManagementAgent* agent);
				QPID_BROKER_EXTERN ~PackageACL() {}
			};

		}
	}
}            

#endif  /*!QPID_BROKER_MANAGE_PACKAGE_ACL_H*/