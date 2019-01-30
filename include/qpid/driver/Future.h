
#ifndef QPID_DRIVER_FUATURE_H
#define QPID_DRIVER_FUATURE_H 1

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


#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include "qpid/sys/Exception.h"
#include "qpid/framing/SequenceNumber.h"
#include "qpid/driver/FutureCompletion.h"
#include "qpid/driver/FutureResult.h"
#include "qpid/driver/Compile.h"

namespace qpid {
namespace driver {

/**@internal */
class QPID_DRIVER_CLASS_EXTERN Future
{
    framing::SequenceNumber command;
    boost::shared_ptr<FutureResult> result;
    bool complete;

public:
    Future() : complete(false) {}
    Future(const framing::SequenceNumber& id) : command(id), complete(false) {}

    std::string getResult(SessionImpl& session) {
        if (result) return result->getResult(session);
        else throw sys::Exception("Result not expected");
    }

    QPID_DRIVER_EXTERN void wait(SessionImpl& session);
	QPID_DRIVER_EXTERN bool isComplete(SessionImpl& session);
	QPID_DRIVER_EXTERN void setFutureResult(boost::shared_ptr<FutureResult> r);
};

}}

#endif  /**QPID_DRIVER_FUATURE_H*/
