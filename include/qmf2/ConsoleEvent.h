#ifndef QMF2_CONSOLE_EVENT_H
#define QMF2_CONSOLE_EVENT_H
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
#include "qmf2/Agent.h"
#include "qmf2/Data.h"
#include "qmf2/SchemaId.h"
#include "qpid/types/Variant.h"

namespace qmf2 {

#ifndef SWIG
    template <class> class PrivateImplRef;
#endif

    class ConsoleEventImpl;

    enum ConsoleEventCode {
    CONSOLE_AGENT_ADD             = 1,
    CONSOLE_AGENT_DEL             = 2,
    CONSOLE_AGENT_RESTART         = 3,
    CONSOLE_AGENT_SCHEMA_UPDATE   = 4,
    CONSOLE_AGENT_SCHEMA_RESPONSE = 5,
    CONSOLE_EVENT                 = 6,
    CONSOLE_QUERY_RESPONSE        = 7,
    CONSOLE_METHOD_RESPONSE       = 8,
    CONSOLE_EXCEPTION             = 9,
    CONSOLE_SUBSCRIBE_ADD         = 10,
    CONSOLE_SUBSCRIBE_UPDATE      = 11,
    CONSOLE_SUBSCRIBE_DEL         = 12,
    CONSOLE_THREAD_FAILED         = 13
    };

    enum AgentDelReason {
    AGENT_DEL_AGED   = 1,
    AGENT_DEL_FILTER = 2 
    };

    class QMF2_CLASS_EXTERN ConsoleEvent : public qmf2::Handle<ConsoleEventImpl> {
    public:
        QMF2_EXTERN ConsoleEvent(ConsoleEventImpl* impl = 0);
        QMF2_EXTERN ConsoleEvent(const ConsoleEvent&);
        QMF2_EXTERN ConsoleEvent& operator=(const ConsoleEvent&);
        QMF2_EXTERN ~ConsoleEvent();

        QMF2_EXTERN ConsoleEventCode getType() const;
        QMF2_EXTERN uint32_t getCorrelator() const;
        QMF2_EXTERN Agent getAgent() const;
        QMF2_EXTERN AgentDelReason getAgentDelReason() const;
        QMF2_EXTERN uint32_t getSchemaIdCount() const;
        QMF2_EXTERN SchemaId getSchemaId(uint32_t) const;
        QMF2_EXTERN uint32_t getDataCount() const;
        QMF2_EXTERN Data getData(uint32_t) const;
        QMF2_EXTERN bool isFinal() const;
        QMF2_EXTERN const qpid::types::Variant::Map& getArguments() const;
        QMF2_EXTERN int getSeverity() const;
        QMF2_EXTERN uint64_t getTimestamp() const;

#ifndef SWIG
    private:
        friend class qmf2::PrivateImplRef<ConsoleEvent>;
        friend struct ConsoleEventImplAccess;
#endif
    };

}

#endif
