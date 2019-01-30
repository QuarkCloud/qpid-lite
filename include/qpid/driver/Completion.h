#ifndef QPID_DRIVER_COMPLETION_H
#define QPID_DRIVER_COMPLETION_H 1

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
#include "qpid/driver/Compile.h"
#include "qpid/driver/Handle.h"
#include "qpid/driver/CompletionImpl.h"

#include <string>

namespace qpid {
namespace driver {

template <class T> class PrivateImplRef;

/**
 * Asynchronous commands that do not return a result will return a
 * Completion. You can use the completion to wait for that specific
 * command to complete.
 *
 *@see TypedResult
 *
 *\ingroup clientapi
 */
class QPID_DRIVER_CLASS_EXTERN Completion : public Handle<CompletionImpl>
{
public:
    QPID_DRIVER_EXTERN Completion(CompletionImpl* = 0);
    QPID_DRIVER_EXTERN Completion(const Completion&);
    QPID_DRIVER_EXTERN ~Completion();
    QPID_DRIVER_EXTERN Completion& operator=(const Completion&);

    /** Wait for the asynchronous command that returned this
     *Completion to complete.
     *
     *@exception If the command returns an error.
     */
    QPID_DRIVER_EXTERN void wait();
    QPID_DRIVER_EXTERN bool isComplete();

  protected:
    QPID_DRIVER_EXTERN std::string getResult();

  private:
    typedef CompletionImpl Impl;
    friend class PrivateImplRef<Completion>;
};

}}


#endif  /*!QPID_DRIVER_COMPLETION_H*/
