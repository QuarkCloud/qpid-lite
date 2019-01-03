#ifndef QMF2_AGENT_EVENT_H
#define QMF2_AGENT_EVENT_H
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

#if !defined(QMF2_USE_DEPRECATED_API) && !defined(qmf2_EXPORTS) && !defined(SWIG)
#  error "The API defined in this file has been DEPRECATED and will be removed in the future."
#  error "Define 'QMF2_USE_DEPRECATED_API' to enable continued use of the API."
#endif

#include <qmf2/Compile.h>
#include "qmf2/Handle.h"
#include "qpid/types/Variant.h"

namespace qmf2 {

#ifndef SWIG
    template <class> class PrivateImplRef;
#endif

    class AgentEventImpl;
    class Query;
    class DataAddr;

    enum AgentEventCode {
    AGENT_AUTH_QUERY      = 1,
    AGENT_AUTH_SUBSCRIBE  = 2,
    AGENT_QUERY           = 3,
    AGENT_METHOD          = 4,
    AGENT_SUBSCRIBE_BEGIN = 5,
    AGENT_SUBSCRIBE_TOUCH = 6,
    AGENT_SUBSCRIBE_END   = 7,
    AGENT_THREAD_FAILED   = 8
    };

    class QMF2_CLASS_EXTERN AgentEvent : public qmf2::Handle<AgentEventImpl> {
    public:
        QMF2_EXTERN AgentEvent(AgentEventImpl* impl = 0);
        QMF2_EXTERN AgentEvent(const AgentEvent&);
        QMF2_EXTERN AgentEvent& operator=(const AgentEvent&);
        QMF2_EXTERN ~AgentEvent();

        QMF2_EXTERN AgentEventCode getType() const;
        QMF2_EXTERN const std::string& getUserId() const;
        QMF2_EXTERN Query getQuery() const;
        QMF2_EXTERN bool hasDataAddr() const;
        QMF2_EXTERN DataAddr getDataAddr() const;
        QMF2_EXTERN const std::string& getMethodName() const;
        QMF2_EXTERN qpid::types::Variant::Map& getArguments();
        QMF2_EXTERN qpid::types::Variant::Map& getArgumentSubtypes();
        QMF2_EXTERN void addReturnArgument(const std::string&, const qpid::types::Variant&, const std::string& st="");

#ifndef SWIG
    private:
        friend class qmf2::PrivateImplRef<AgentEvent>;
        friend struct AgentEventImplAccess;
#endif
    };
}

#endif
