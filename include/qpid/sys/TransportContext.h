#ifndef QPID_SYS_TRANSPORT_CONTEXT_H
#define QPID_SYS_TRANSPORT_CONTEXT_H 1

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
#include "qpid/sys/Codec.h"
#include "qpid/sys/ConnectionSettings.h"

namespace qpid {
	namespace sys {

		/**
		 * Interface to be supplied by 'users' of Transport interface, in
		 * order to provide codec and handle callbaskc for opening and closing
		 * of connection.
		 */
		class TransportContext
		{
		public:
			virtual ~TransportContext() {}
			virtual qpid::sys::Codec& getCodec() = 0;
			virtual const ConnectionSettings* getSettings() = 0;
			virtual void closed() = 0;
			virtual void opened() = 0;
		private:
		};
	}
}// namespace qpid::sys

#endif  /*!QPID_SYS_TRANSPORT_CONTEXT_H*/
