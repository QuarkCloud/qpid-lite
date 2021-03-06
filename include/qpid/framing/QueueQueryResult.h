#ifndef QPID_FRAMING_QUEUE_QUERY_RESULT_H
#define QPID_FRAMING_QUEUE_QUERY_RESULT_H 1
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

class QPID_FRAMING_CLASS_EXTERN QueueQueryResult  {
    std::string queue;
    std::string alternateExchange;
    FieldTable arguments;
    uint32_t messageCount;
    uint32_t subscriberCount;
    uint16_t flags;
public:
    static const uint16_t TYPE = 2049;
    QueueQueryResult(
        const std::string& _queue,
        const std::string& _alternateExchange,
        bool _durable,
        bool _exclusive,
        bool _autoDelete,
        const FieldTable& _arguments,
        uint32_t _messageCount,
        uint32_t _subscriberCount) : 
        queue(_queue),
        alternateExchange(_alternateExchange),
        arguments(_arguments),
        messageCount(_messageCount),
        subscriberCount(_subscriberCount),
        flags(0){
        setDurable(_durable);
        setExclusive(_exclusive);
        setAutoDelete(_autoDelete);
        flags |= (1 << 8);
        flags |= (1 << 9);
        flags |= (1 << 13);
        flags |= (1 << 14);
        flags |= (1 << 15);
        if (queue.size() >= 256) throw IllegalArgumentException("Value for queue is too large");
        if (alternateExchange.size() >= 256) throw IllegalArgumentException("Value for alternateExchange is too large");
    }
    QueueQueryResult()  : messageCount(0), subscriberCount(0), flags(0) {}
    
    QPID_FRAMING_EXTERN void setQueue(const std::string& _queue);
    QPID_FRAMING_EXTERN const std::string& getQueue() const;
    QPID_FRAMING_EXTERN bool hasQueue() const;
    QPID_FRAMING_EXTERN void clearQueueFlag();
    QPID_FRAMING_EXTERN void setAlternateExchange(const std::string& _alternateExchange);
    QPID_FRAMING_EXTERN const std::string& getAlternateExchange() const;
    QPID_FRAMING_EXTERN bool hasAlternateExchange() const;
    QPID_FRAMING_EXTERN void clearAlternateExchangeFlag();
    QPID_FRAMING_EXTERN void setDurable(bool _durable);
    QPID_FRAMING_EXTERN bool getDurable() const;
    QPID_FRAMING_EXTERN void setExclusive(bool _exclusive);
    QPID_FRAMING_EXTERN bool getExclusive() const;
    QPID_FRAMING_EXTERN void setAutoDelete(bool _autoDelete);
    QPID_FRAMING_EXTERN bool getAutoDelete() const;
    QPID_FRAMING_EXTERN void setArguments(const FieldTable& _arguments);
    QPID_FRAMING_EXTERN const FieldTable& getArguments() const;
    QPID_FRAMING_EXTERN FieldTable& getArguments();
    QPID_FRAMING_EXTERN bool hasArguments() const;
    QPID_FRAMING_EXTERN void clearArgumentsFlag();
    QPID_FRAMING_EXTERN void setMessageCount(uint32_t _messageCount);
    QPID_FRAMING_EXTERN uint32_t getMessageCount() const;
    QPID_FRAMING_EXTERN bool hasMessageCount() const;
    QPID_FRAMING_EXTERN void clearMessageCountFlag();
    QPID_FRAMING_EXTERN void setSubscriberCount(uint32_t _subscriberCount);
    QPID_FRAMING_EXTERN uint32_t getSubscriberCount() const;
    QPID_FRAMING_EXTERN bool hasSubscriberCount() const;
    QPID_FRAMING_EXTERN void clearSubscriberCountFlag();
    QPID_FRAMING_EXTERN friend std::ostream& operator<<(std::ostream&, const QueueQueryResult&);
    QPID_FRAMING_EXTERN void encode(Buffer&) const;
    QPID_FRAMING_EXTERN void decode(Buffer&, uint32_t=0);
    QPID_FRAMING_EXTERN void encodeStructBody(Buffer&) const;
    QPID_FRAMING_EXTERN void decodeStructBody(Buffer&, uint32_t=0);
    QPID_FRAMING_EXTERN uint32_t encodedSize() const;
    QPID_FRAMING_EXTERN uint32_t bodySize() const;
    QPID_FRAMING_EXTERN void print(std::ostream& out) const;
}; /* class QueueQueryResult */

}}
#endif  /*!QPID_FRAMING_QUEUE_QUERY_RESULT_H*/
