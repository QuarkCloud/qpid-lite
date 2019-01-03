#ifndef QPID_SYS_DISPATCHER_H
#define QPID_SYS_DISPATCHER_H 1

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
#include "qpid/sys/Compile.h"
#include "qpid/sys/Poller.h"
#include "qpid/sys/Runnable.h"


namespace qpid {
namespace sys {

class Dispatcher : public Runnable {
    const Poller::shared_ptr poller;

public:
    QPID_SYS_EXTERN Dispatcher(Poller::shared_ptr poller);
	QPID_SYS_EXTERN ~Dispatcher();
    
	QPID_SYS_EXTERN void run();
};

}}

#endif // QPID_SYS_DISPATCHER_H