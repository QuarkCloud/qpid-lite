#ifndef QPID_FRAMING_FILE_REJECT_BODY_H
#define QPID_FRAMING_FILE_REJECT_BODY_H 1
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

class QPID_FRAMING_CLASS_EXTERN FileRejectBody : public ModelMethod {
    uint64_t deliveryTag;
    uint16_t flags;
public:
    static const ClassId CLASS_ID = 0x9;
    static const MethodId METHOD_ID = 0xd;
    FileRejectBody(
        ProtocolVersion, uint64_t _deliveryTag,
        bool _requeue) : 
        deliveryTag(_deliveryTag),
        flags(0){
        setRequeue(_requeue);
        flags |= (1 << 8);
    }
    FileRejectBody(ProtocolVersion=ProtocolVersion())  : deliveryTag(0), flags(0) {}
    
    QPID_FRAMING_EXTERN void setDeliveryTag(uint64_t _deliveryTag);
    QPID_FRAMING_EXTERN uint64_t getDeliveryTag() const;
    QPID_FRAMING_EXTERN bool hasDeliveryTag() const;
    QPID_FRAMING_EXTERN void clearDeliveryTagFlag();
    QPID_FRAMING_EXTERN void setRequeue(bool _requeue);
    QPID_FRAMING_EXTERN bool getRequeue() const;
    typedef void ResultType;

    template <class T> ResultType invoke(T& invocable) const {
        return invocable.reject(getDeliveryTag(), getRequeue());
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
}; /* class FileRejectBody */

}}
#endif  /*!QPID_FRAMING_FILE_REJECT_BODY_H*/
