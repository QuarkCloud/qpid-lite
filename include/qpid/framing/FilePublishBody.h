#ifndef QPID_FRAMING_FILE_PUBLISH_BODY_H
#define QPID_FRAMING_FILE_PUBLISH_BODY_H 1
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

class QPID_FRAMING_CLASS_EXTERN FilePublishBody : public ModelMethod {
    std::string exchange;
    std::string routingKey;
    std::string identifier;
    uint16_t flags;
public:
    static const ClassId CLASS_ID = 0x9;
    static const MethodId METHOD_ID = 0x9;
    FilePublishBody(
        ProtocolVersion, const std::string& _exchange,
        const std::string& _routingKey,
        bool _mandatory,
        bool _immediate,
        const std::string& _identifier) : 
        exchange(_exchange),
        routingKey(_routingKey),
        identifier(_identifier),
        flags(0){
        setMandatory(_mandatory);
        setImmediate(_immediate);
        flags |= (1 << 8);
        flags |= (1 << 9);
        flags |= (1 << 12);
        if (exchange.size() >= 256) throw IllegalArgumentException("Value for exchange is too large");
        if (routingKey.size() >= 256) throw IllegalArgumentException("Value for routingKey is too large");
        if (identifier.size() >= 256) throw IllegalArgumentException("Value for identifier is too large");
    }
    FilePublishBody(ProtocolVersion=ProtocolVersion())  : flags(0) {}
    
    QPID_FRAMING_EXTERN void setExchange(const std::string& _exchange);
    QPID_FRAMING_EXTERN const std::string& getExchange() const;
    QPID_FRAMING_EXTERN bool hasExchange() const;
    QPID_FRAMING_EXTERN void clearExchangeFlag();
    QPID_FRAMING_EXTERN void setRoutingKey(const std::string& _routingKey);
    QPID_FRAMING_EXTERN const std::string& getRoutingKey() const;
    QPID_FRAMING_EXTERN bool hasRoutingKey() const;
    QPID_FRAMING_EXTERN void clearRoutingKeyFlag();
    QPID_FRAMING_EXTERN void setMandatory(bool _mandatory);
    QPID_FRAMING_EXTERN bool getMandatory() const;
    QPID_FRAMING_EXTERN void setImmediate(bool _immediate);
    QPID_FRAMING_EXTERN bool getImmediate() const;
    QPID_FRAMING_EXTERN void setIdentifier(const std::string& _identifier);
    QPID_FRAMING_EXTERN const std::string& getIdentifier() const;
    QPID_FRAMING_EXTERN bool hasIdentifier() const;
    QPID_FRAMING_EXTERN void clearIdentifierFlag();
    typedef void ResultType;

    template <class T> ResultType invoke(T& invocable) const {
        return invocable.publish(getExchange(), getRoutingKey(), getMandatory(), getImmediate(), getIdentifier());
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
}; /* class FilePublishBody */

}}
#endif  /*!QPID_FRAMING_FILE_PUBLISH_BODY_H*/
