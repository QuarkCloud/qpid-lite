#ifndef QPID_FRAMING_DTX_RECOVER_RESULT_H
#define QPID_FRAMING_DTX_RECOVER_RESULT_H 1
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

class QPID_FRAMING_CLASS_EXTERN DtxRecoverResult  {
    Array inDoubt;
    uint16_t flags;
public:
    static const uint16_t TYPE = 1539;
    DtxRecoverResult(
        const Array& _inDoubt) : 
        inDoubt(_inDoubt),
        flags(0){
        flags |= (1 << 8);
    }
    DtxRecoverResult()  : flags(0) {}
    
    QPID_FRAMING_EXTERN void setInDoubt(const Array& _inDoubt);
    QPID_FRAMING_EXTERN const Array& getInDoubt() const;
    QPID_FRAMING_EXTERN bool hasInDoubt() const;
    QPID_FRAMING_EXTERN void clearInDoubtFlag();
    QPID_FRAMING_EXTERN friend std::ostream& operator<<(std::ostream&, const DtxRecoverResult&);
    QPID_FRAMING_EXTERN void encode(Buffer&) const;
    QPID_FRAMING_EXTERN void decode(Buffer&, uint32_t=0);
    QPID_FRAMING_EXTERN void encodeStructBody(Buffer&) const;
    QPID_FRAMING_EXTERN void decodeStructBody(Buffer&, uint32_t=0);
    QPID_FRAMING_EXTERN uint32_t encodedSize() const;
    QPID_FRAMING_EXTERN uint32_t bodySize() const;
    QPID_FRAMING_EXTERN void print(std::ostream& out) const;
}; /* class DtxRecoverResult */

}}
#endif  /*!QPID_FRAMING_DTX_RECOVER_RESULT_H*/
