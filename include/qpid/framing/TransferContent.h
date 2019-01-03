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
#ifndef QPID_FRAMING_TRANSFER_CONTENT_H
#define QPID_FRAMING_TRANSFER_CONTENT_H 1

#include "qpid/framing/FrameSet.h"
#include "qpid/framing/MethodContent.h"
#include "qpid/sys/Exception.h"
#include "qpid/framing/MessageProperties.h"
#include "qpid/framing/DeliveryProperties.h"
#include "qpid/framing/Compile.h"

namespace qpid {
namespace framing {

/** Message content */
class QPID_FRAMING_CLASS_EXTERN TransferContent : public MethodContent
{
    AMQHeaderBody header;
    std::string data;
public:
    QPID_FRAMING_EXTERN	TransferContent(const std::string& data = std::string(), const std::string& key=std::string());

    ///@internal
    QPID_FRAMING_EXTERN const AMQHeaderBody& getHeader() const;

    QPID_FRAMING_EXTERN void setData(const std::string&);
    QPID_FRAMING_EXTERN const std::string& getData() const;
    QPID_FRAMING_EXTERN std::string& getData();

    QPID_FRAMING_EXTERN void appendData(const std::string&);

    QPID_FRAMING_EXTERN bool hasMessageProperties() const;
    QPID_FRAMING_EXTERN MessageProperties& getMessageProperties();
    QPID_FRAMING_EXTERN const MessageProperties& getMessageProperties() const;

    QPID_FRAMING_EXTERN bool hasDeliveryProperties() const;
    QPID_FRAMING_EXTERN DeliveryProperties& getDeliveryProperties();
    QPID_FRAMING_EXTERN const DeliveryProperties& getDeliveryProperties() const;

    ///@internal
    QPID_FRAMING_EXTERN void populate(const FrameSet& frameset);
};

}}
#endif  /**QPID_FRAMING_TRANSFER_CONTENT_H*/
