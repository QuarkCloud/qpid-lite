#ifndef QPID_FRAMING_EXECUTION_RESULT_BODY_H
#define QPID_FRAMING_EXECUTION_RESULT_BODY_H 1
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

///
/// This file was automatically generated from the AMQP specification.
/// Do not edit.
///


#include "qpid/framing/AMQMethodBody.h"
#include "qpid/framing/AMQP_ServerOperations.h"
#include "qpid/framing/MethodBodyConstVisitor.h"
#include "qpid/framing/ModelMethod.h"

#include <ostream>
#include "qpid/framing/amqp_types_full.h"
#include "qpid/framing/reply_exceptions.h"
#include "qpid/framing/Compile.h"

namespace qpid {
namespace framing {

class QPID_FRAMING_CLASS_EXTERN ExecutionResultBody : public ModelMethod {
    SequenceNumber commandId;
    std::string value;
    uint16_t flags;
public:
    static const ClassId CLASS_ID = 0x3;
    static const MethodId METHOD_ID = 0x2;
    ExecutionResultBody(
        ProtocolVersion, const SequenceNumber& _commandId,
        const std::string& _value) : 
        commandId(_commandId),
        value(_value),
        flags(0){
        flags |= (1 << 8);
        flags |= (1 << 9);
    }
    ExecutionResultBody(ProtocolVersion=ProtocolVersion())  : flags(0) {}
    
    QPID_FRAMING_EXTERN void setCommandId(const SequenceNumber& _commandId);
    QPID_FRAMING_EXTERN SequenceNumber getCommandId() const;
    QPID_FRAMING_EXTERN bool hasCommandId() const;
    QPID_FRAMING_EXTERN void clearCommandIdFlag();
    QPID_FRAMING_EXTERN void setValue(const std::string& _value);
    QPID_FRAMING_EXTERN const std::string& getValue() const;
    QPID_FRAMING_EXTERN bool hasValue() const;
    QPID_FRAMING_EXTERN void clearValueFlag();
    typedef void ResultType;

    template <class T> ResultType invoke(T& invocable) const {
        return invocable.result(getCommandId(), getValue());
    }

    using  AMQMethodBody::accept;
    void accept(MethodBodyConstVisitor& v) const { v.visit(*this); }
    boost::intrusive_ptr<AMQBody> clone() const { return BodyFactory::copy(*this); }

    ClassId amqpClassId() const { return CLASS_ID; }
    MethodId amqpMethodId() const { return METHOD_ID; }
    bool isContentBearing() const { return  false; }
    bool resultExpected() const { return  false; }
    bool responseExpected() const { return  false; }
    QPID_FRAMING_EXTERN void encode(Buffer&) const;
    QPID_FRAMING_EXTERN void decode(Buffer&, uint32_t=0);
    QPID_FRAMING_EXTERN void encodeStructBody(Buffer&) const;
    QPID_FRAMING_EXTERN void decodeStructBody(Buffer&, uint32_t=0);
    QPID_FRAMING_EXTERN uint32_t encodedSize() const;
    QPID_FRAMING_EXTERN uint32_t bodySize() const;
    QPID_FRAMING_EXTERN void print(std::ostream& out) const;
}; /* class ExecutionResultBody */

}}
#endif  /*!QPID_FRAMING_EXECUTION_RESULT_BODY_H */
