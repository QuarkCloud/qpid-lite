#ifndef QPID_MESSAGING_AMQP_LIST_BUILDER_H
#define QPID_MESSAGING_AMQP_LIST_BUILDER_H 1

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
#include "qpid/messaging/amqp/DataBuilder.h"
#include "qpid/messaging/Compile.h"

namespace qpid {
	namespace messaging {
		namespace amqp {

			/**
			 * Utility to build a Variant::List from a data stream
			 */
			class ListBuilder : public DataBuilder
			{
			public:
				QPID_MESSAGING_EXTERN ListBuilder();
				QPID_MESSAGING_EXTERN qpid::types::Variant::List& getList();
			};
		}
	}
} // namespace qpid::messaging::amqp

#endif  /*!QPID_MESSAGING_AMQP_LIST_BUILDER_H*/
