#ifndef QPID_FRAMING_DELIVERY_PROPERTIES_H
#define QPID_FRAMING_DELIVERY_PROPERTIES_H 1
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



#include <ostream>
#include "qpid/framing/amqp_types_full.h"
#include "qpid/framing/reply_exceptions.h"
#include "qpid/framing/Compile.h"

namespace qpid {
namespace framing {

class QPID_FRAMING_CLASS_EXTERN DeliveryProperties  {
    uint8_t priority;
    uint8_t deliveryMode;
    uint64_t ttl;
    uint64_t timestamp;
    uint64_t expiration;
    std::string exchange;
    std::string routingKey;
    std::string resumeId;
    uint64_t resumeTtl;
    uint16_t flags;
public:
    static const uint16_t TYPE = 1025;
    DeliveryProperties(
        bool _discardUnroutable,
        bool _immediate,
        bool _redelivered,
        uint8_t _priority,
        uint8_t _deliveryMode,
        uint64_t _ttl,
        uint64_t _timestamp,
        uint64_t _expiration,
        const std::string& _exchange,
        const std::string& _routingKey,
        const std::string& _resumeId,
        uint64_t _resumeTtl) : 
        priority(_priority),
        deliveryMode(_deliveryMode),
        ttl(_ttl),
        timestamp(_timestamp),
        expiration(_expiration),
        exchange(_exchange),
        routingKey(_routingKey),
        resumeId(_resumeId),
        resumeTtl(_resumeTtl),
        flags(0){
        setDiscardUnroutable(_discardUnroutable);
        setImmediate(_immediate);
        setRedelivered(_redelivered);
        flags |= (1 << 11);
        flags |= (1 << 12);
        flags |= (1 << 13);
        flags |= (1 << 14);
        flags |= (1 << 15);
        flags |= (1 << 0);
        flags |= (1 << 1);
        flags |= (1 << 2);
        flags |= (1 << 3);
        if (exchange.size() >= 256) throw IllegalArgumentException("Value for exchange is too large");
        if (routingKey.size() >= 256) throw IllegalArgumentException("Value for routingKey is too large");
        if (resumeId.size() >= 65536) throw IllegalArgumentException("Value for resumeId is too large");
    }
    DeliveryProperties()  : priority(0), deliveryMode(0), ttl(0), timestamp(0), expiration(0), resumeTtl(0), flags(0) {}
    
    QPID_FRAMING_EXTERN void setDiscardUnroutable(bool _discardUnroutable);
    QPID_FRAMING_EXTERN bool getDiscardUnroutable() const;
    QPID_FRAMING_EXTERN void setImmediate(bool _immediate);
    QPID_FRAMING_EXTERN bool getImmediate() const;
    QPID_FRAMING_EXTERN void setRedelivered(bool _redelivered);
    QPID_FRAMING_EXTERN bool getRedelivered() const;
    QPID_FRAMING_EXTERN void setPriority(uint8_t _priority);
    QPID_FRAMING_EXTERN uint8_t getPriority() const;
    QPID_FRAMING_EXTERN bool hasPriority() const;
    QPID_FRAMING_EXTERN void clearPriorityFlag();
    QPID_FRAMING_EXTERN void setDeliveryMode(uint8_t _deliveryMode);
    QPID_FRAMING_EXTERN uint8_t getDeliveryMode() const;
    QPID_FRAMING_EXTERN bool hasDeliveryMode() const;
    QPID_FRAMING_EXTERN void clearDeliveryModeFlag();
    QPID_FRAMING_EXTERN void setTtl(uint64_t _ttl);
    QPID_FRAMING_EXTERN uint64_t getTtl() const;
    QPID_FRAMING_EXTERN bool hasTtl() const;
    QPID_FRAMING_EXTERN void clearTtlFlag();
    QPID_FRAMING_EXTERN void setTimestamp(uint64_t _timestamp);
    QPID_FRAMING_EXTERN uint64_t getTimestamp() const;
    QPID_FRAMING_EXTERN bool hasTimestamp() const;
    QPID_FRAMING_EXTERN void clearTimestampFlag();
    QPID_FRAMING_EXTERN void setExpiration(uint64_t _expiration);
    QPID_FRAMING_EXTERN uint64_t getExpiration() const;
    QPID_FRAMING_EXTERN bool hasExpiration() const;
    QPID_FRAMING_EXTERN void clearExpirationFlag();
    QPID_FRAMING_EXTERN void setExchange(const std::string& _exchange);
    QPID_FRAMING_EXTERN const std::string& getExchange() const;
    QPID_FRAMING_EXTERN bool hasExchange() const;
    QPID_FRAMING_EXTERN void clearExchangeFlag();
    QPID_FRAMING_EXTERN void setRoutingKey(const std::string& _routingKey);
    QPID_FRAMING_EXTERN const std::string& getRoutingKey() const;
    QPID_FRAMING_EXTERN bool hasRoutingKey() const;
    QPID_FRAMING_EXTERN void clearRoutingKeyFlag();
    QPID_FRAMING_EXTERN void setResumeId(const std::string& _resumeId);
    QPID_FRAMING_EXTERN const std::string& getResumeId() const;
    QPID_FRAMING_EXTERN bool hasResumeId() const;
    QPID_FRAMING_EXTERN void clearResumeIdFlag();
    QPID_FRAMING_EXTERN void setResumeTtl(uint64_t _resumeTtl);
    QPID_FRAMING_EXTERN uint64_t getResumeTtl() const;
    QPID_FRAMING_EXTERN bool hasResumeTtl() const;
    QPID_FRAMING_EXTERN void clearResumeTtlFlag();
    QPID_FRAMING_EXTERN friend std::ostream& operator<<(std::ostream&, const DeliveryProperties&);
    QPID_FRAMING_EXTERN void encode(Buffer&) const;
    QPID_FRAMING_EXTERN void decode(Buffer&, uint32_t=0);
    QPID_FRAMING_EXTERN void encodeStructBody(Buffer&) const;
    QPID_FRAMING_EXTERN void decodeStructBody(Buffer&, uint32_t=0);
    QPID_FRAMING_EXTERN uint32_t encodedSize() const;
    QPID_FRAMING_EXTERN uint32_t bodySize() const;
    QPID_FRAMING_EXTERN void print(std::ostream& out) const;
}; /* class DeliveryProperties */

}}
#endif  /*!QPID_FRAMING_DELIVERY_PROPERTIES_H*/
