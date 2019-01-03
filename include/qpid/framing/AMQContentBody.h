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
#ifndef QPID_FRAMING_AMQ_CONTENT_BODY_H
#define QPID_FRAMING_AMQ_CONTENT_BODY_H 1


#include "qpid/framing/amqp_types.h"
#include "qpid/framing/AMQBody.h"
#include "qpid/framing/Buffer.h"
#include "qpid/framing/Compile.h"


namespace qpid {
namespace framing {

class QPID_FRAMING_CLASS_EXTERN AMQContentBody :  public AMQBody
{
    std::string data;

public:
    QPID_FRAMING_EXTERN AMQContentBody();
    QPID_FRAMING_EXTERN AMQContentBody(const std::string& data);
    inline virtual ~AMQContentBody(){}
    inline uint8_t type() const { return CONTENT_BODY; };
    inline const std::string& getData() const { return data; }
    inline std::string& getData() { return data; }
    QPID_FRAMING_EXTERN uint32_t encodedSize() const;
    QPID_FRAMING_EXTERN void encode(Buffer& buffer) const;
    QPID_FRAMING_EXTERN void decode(Buffer& buffer, uint32_t size);
    QPID_FRAMING_EXTERN void print(std::ostream& out) const;
    void accept(AMQBodyConstVisitor& v) const { v.visit(*this); }
    boost::intrusive_ptr<AMQBody> clone() const { return BodyFactory::copy(*this); }
};

}
}


#endif /** QPID_FRAMING_AMQ_CONTENT_BODY_H */
