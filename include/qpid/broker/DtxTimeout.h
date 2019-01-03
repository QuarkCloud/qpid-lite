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
#ifndef _DtxTimeout_
#define _DtxTimeout_

#include "qpid/sys/Exception.h"
#include "qpid/sys/Timer.h"

namespace qpid {
namespace broker {

class DtxManager;

struct DtxTimeoutException : public qpid::sys::Exception {
    DtxTimeoutException(const std::string& msg=std::string()) : qpid::sys::Exception(msg) {}
};

struct DtxTimeout : public sys::TimerTask
{
    const uint32_t timeout;
    DtxManager& mgr;
    const std::string xid;

    DtxTimeout(uint32_t timeout, DtxManager& mgr, const std::string& xid);
    void fire();
};

}
}


#endif
