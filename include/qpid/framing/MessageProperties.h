#ifndef QPID_FRAMING_MESSAGE_PROPERTIES_H
#define QPID_FRAMING_MESSAGE_PROPERTIES_H 1
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


#include "qpid/framing/ReplyTo.h"

#include <ostream>
#include "qpid/framing/amqp_types_full.h"
#include "qpid/framing/reply_exceptions.h"
#include "qpid/framing/Compile.h"

namespace qpid {
namespace framing {

class QPID_FRAMING_CLASS_EXTERN MessageProperties  {
    uint64_t contentLength;
    Uuid messageId;
    std::string correlationId;
    ReplyTo replyTo;
    std::string contentType;
    std::string contentEncoding;
    std::string userId;
    std::string appId;
    FieldTable applicationHeaders;
    uint16_t flags;
public:
    static const uint16_t TYPE = 1027;
    MessageProperties(
        uint64_t _contentLength,
        const Uuid& _messageId,
        const std::string& _correlationId,
        const ReplyTo& _replyTo,
        const std::string& _contentType,
        const std::string& _contentEncoding,
        const std::string& _userId,
        const std::string& _appId,
        const FieldTable& _applicationHeaders) : 
        contentLength(_contentLength),
        messageId(_messageId),
        correlationId(_correlationId),
        replyTo(_replyTo),
        contentType(_contentType),
        contentEncoding(_contentEncoding),
        userId(_userId),
        appId(_appId),
        applicationHeaders(_applicationHeaders),
        flags(0){
        flags |= (1 << 8);
        flags |= (1 << 9);
        flags |= (1 << 10);
        flags |= (1 << 11);
        flags |= (1 << 12);
        flags |= (1 << 13);
        flags |= (1 << 14);
        flags |= (1 << 15);
        flags |= (1 << 0);
        if (correlationId.size() >= 65536) throw IllegalArgumentException("Value for correlationId is too large");
        if (contentType.size() >= 256) throw IllegalArgumentException("Value for contentType is too large");
        if (contentEncoding.size() >= 256) throw IllegalArgumentException("Value for contentEncoding is too large");
        if (userId.size() >= 65536) throw IllegalArgumentException("Value for userId is too large");
        if (appId.size() >= 65536) throw IllegalArgumentException("Value for appId is too large");
    }
    MessageProperties()  : contentLength(0), flags(0) {}
    
    QPID_FRAMING_EXTERN void setContentLength(uint64_t _contentLength);
    QPID_FRAMING_EXTERN uint64_t getContentLength() const;
    QPID_FRAMING_EXTERN bool hasContentLength() const;
    QPID_FRAMING_EXTERN void clearContentLengthFlag();
    QPID_FRAMING_EXTERN void setMessageId(const Uuid& _messageId);
    QPID_FRAMING_EXTERN const Uuid& getMessageId() const;
    QPID_FRAMING_EXTERN bool hasMessageId() const;
    QPID_FRAMING_EXTERN void clearMessageIdFlag();
    QPID_FRAMING_EXTERN void setCorrelationId(const std::string& _correlationId);
    QPID_FRAMING_EXTERN const std::string& getCorrelationId() const;
    QPID_FRAMING_EXTERN bool hasCorrelationId() const;
    QPID_FRAMING_EXTERN void clearCorrelationIdFlag();
    QPID_FRAMING_EXTERN void setReplyTo(const ReplyTo& _replyTo);
    QPID_FRAMING_EXTERN const ReplyTo& getReplyTo() const;
    QPID_FRAMING_EXTERN bool hasReplyTo() const;
    QPID_FRAMING_EXTERN void clearReplyToFlag();
    QPID_FRAMING_EXTERN void setContentType(const std::string& _contentType);
    QPID_FRAMING_EXTERN const std::string& getContentType() const;
    QPID_FRAMING_EXTERN bool hasContentType() const;
    QPID_FRAMING_EXTERN void clearContentTypeFlag();
    QPID_FRAMING_EXTERN void setContentEncoding(const std::string& _contentEncoding);
    QPID_FRAMING_EXTERN const std::string& getContentEncoding() const;
    QPID_FRAMING_EXTERN bool hasContentEncoding() const;
    QPID_FRAMING_EXTERN void clearContentEncodingFlag();
    QPID_FRAMING_EXTERN void setUserId(const std::string& _userId);
    QPID_FRAMING_EXTERN const std::string& getUserId() const;
    QPID_FRAMING_EXTERN bool hasUserId() const;
    QPID_FRAMING_EXTERN void clearUserIdFlag();
    QPID_FRAMING_EXTERN void setAppId(const std::string& _appId);
    QPID_FRAMING_EXTERN const std::string& getAppId() const;
    QPID_FRAMING_EXTERN bool hasAppId() const;
    QPID_FRAMING_EXTERN void clearAppIdFlag();
    QPID_FRAMING_EXTERN void setApplicationHeaders(const FieldTable& _applicationHeaders);
    QPID_FRAMING_EXTERN const FieldTable& getApplicationHeaders() const;
    QPID_FRAMING_EXTERN FieldTable& getApplicationHeaders();
    QPID_FRAMING_EXTERN bool hasApplicationHeaders() const;
    QPID_FRAMING_EXTERN void clearApplicationHeadersFlag();
    QPID_FRAMING_EXTERN friend std::ostream& operator<<(std::ostream&, const MessageProperties&);
    QPID_FRAMING_EXTERN void encode(Buffer&) const;
    QPID_FRAMING_EXTERN void decode(Buffer&, uint32_t=0);
    QPID_FRAMING_EXTERN void encodeStructBody(Buffer&) const;
    QPID_FRAMING_EXTERN void decodeStructBody(Buffer&, uint32_t=0);
    QPID_FRAMING_EXTERN uint32_t encodedSize() const;
    QPID_FRAMING_EXTERN uint32_t bodySize() const;
    QPID_FRAMING_EXTERN void print(std::ostream& out) const;
}; /* class MessageProperties */

}}
#endif  /*!QPID_FRAMING_MESSAGE_PROPERTIES_H*/
