#ifndef QPID_CLIENT_NO_KEYWORD_SESSION0_10_H
#define QPID_CLIENT_NO_KEYWORD_SESSION0_10_H
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


#include "qpid/client/SessionBase0_10.h"
#include "qpid/client/Compile.h"

namespace qpid {
namespace client {
namespace no_keyword {

/**
 * AMQP 0-10 synchronous session API.
 */
class Session0_10:
    public SessionBase0_10
{
  public:
    
    QPID_CLIENT_EXTERN Session0_10();
    QPID_CLIENT_INLINE_EXTERN Session0_10(const SessionBase0_10& other);
    QPID_CLIENT_INLINE_EXTERN Session0_10& operator=(const SessionBase0_10& other);
    
    QPID_CLIENT_EXTERN void executionSync(bool sync=true);
    
    QPID_CLIENT_EXTERN void executionResult(const SequenceNumber& commandId=SequenceNumber(), const std::string& value=std::string(), bool sync=true);
    
    QPID_CLIENT_EXTERN void executionException(uint16_t errorCode=0, const SequenceNumber& commandId=SequenceNumber(), uint8_t classCode=0, uint8_t commandCode=0, uint8_t fieldIndex=0, const std::string& description=std::string(), const FieldTable& errorInfo=FieldTable(), bool sync=true);
    
    QPID_CLIENT_EXTERN void messageTransfer(const std::string& destination=std::string(), uint8_t acceptMode=1, uint8_t acquireMode=0, const Message& content=Message(std::string()), bool sync=true);
    
    QPID_CLIENT_EXTERN void messageAccept(const SequenceSet& transfers=SequenceSet(), bool sync=true);
    
    QPID_CLIENT_EXTERN void messageReject(const SequenceSet& transfers=SequenceSet(), uint16_t code=0, const std::string& text=std::string(), bool sync=true);
    
    QPID_CLIENT_EXTERN void messageRelease(const SequenceSet& transfers=SequenceSet(), bool setRedelivered=false, bool sync=true);
    
    QPID_CLIENT_EXTERN qpid::framing::MessageAcquireResult messageAcquire(const SequenceSet& transfers=SequenceSet(), bool sync=true);
    
    QPID_CLIENT_EXTERN qpid::framing::MessageResumeResult messageResume(const std::string& destination=std::string(), const std::string& resumeId=std::string(), bool sync=true);
    
    QPID_CLIENT_EXTERN void messageSubscribe(const std::string& queue=std::string(), const std::string& destination=std::string(), uint8_t acceptMode=0, uint8_t acquireMode=0, bool exclusive=false, const std::string& resumeId=std::string(), uint64_t resumeTtl=0, const FieldTable& arguments=FieldTable(), bool sync=true);
    
    QPID_CLIENT_EXTERN void messageCancel(const std::string& destination=std::string(), bool sync=true);
    
    QPID_CLIENT_EXTERN void messageSetFlowMode(const std::string& destination=std::string(), uint8_t flowMode=0, bool sync=true);
    
    QPID_CLIENT_EXTERN void messageFlow(const std::string& destination=std::string(), uint8_t unit=0, uint32_t value=0, bool sync=true);
    
    QPID_CLIENT_EXTERN void messageFlush(const std::string& destination=std::string(), bool sync=true);
    
    QPID_CLIENT_EXTERN void messageStop(const std::string& destination=std::string(), bool sync=true);
    
    QPID_CLIENT_EXTERN void txSelect(bool sync=true);
    
    QPID_CLIENT_EXTERN void txCommit(bool sync=true);
    
    QPID_CLIENT_EXTERN void txRollback(bool sync=true);
    
    QPID_CLIENT_EXTERN void dtxSelect(bool sync=true);
    
    QPID_CLIENT_EXTERN qpid::framing::XaResult dtxStart(const Xid& xid=Xid(), bool join=false, bool resume=false, bool sync=true);
    
    QPID_CLIENT_EXTERN qpid::framing::XaResult dtxEnd(const Xid& xid=Xid(), bool fail=false, bool suspend=false, bool sync=true);
    
    QPID_CLIENT_EXTERN qpid::framing::XaResult dtxCommit(const Xid& xid=Xid(), bool onePhase=false, bool sync=true);
    
    QPID_CLIENT_EXTERN void dtxForget(const Xid& xid=Xid(), bool sync=true);
    
    QPID_CLIENT_EXTERN qpid::framing::DtxGetTimeoutResult dtxGetTimeout(const Xid& xid=Xid(), bool sync=true);
    
    QPID_CLIENT_EXTERN qpid::framing::XaResult dtxPrepare(const Xid& xid=Xid(), bool sync=true);
    
    QPID_CLIENT_EXTERN qpid::framing::DtxRecoverResult dtxRecover(bool sync=true);
    
    QPID_CLIENT_EXTERN qpid::framing::XaResult dtxRollback(const Xid& xid=Xid(), bool sync=true);
    
    QPID_CLIENT_EXTERN void dtxSetTimeout(const Xid& xid=Xid(), uint32_t timeout=0, bool sync=true);
    
    QPID_CLIENT_EXTERN void exchangeDeclare(const std::string& exchange=std::string(), const std::string& type=std::string(), const std::string& alternateExchange=std::string(), bool passive=false, bool durable=false, bool autoDelete=false, const FieldTable& arguments=FieldTable(), bool sync=true);
    
    QPID_CLIENT_EXTERN void exchangeDelete(const std::string& exchange=std::string(), bool ifUnused=false, bool sync=true);
    
    QPID_CLIENT_EXTERN qpid::framing::ExchangeQueryResult exchangeQuery(const std::string& name=std::string(), bool sync=true);
    
    QPID_CLIENT_EXTERN void exchangeBind(const std::string& queue=std::string(), const std::string& exchange=std::string(), const std::string& bindingKey=std::string(), const FieldTable& arguments=FieldTable(), bool sync=true);
    
    QPID_CLIENT_EXTERN void exchangeUnbind(const std::string& queue=std::string(), const std::string& exchange=std::string(), const std::string& bindingKey=std::string(), bool sync=true);
    
    QPID_CLIENT_EXTERN qpid::framing::ExchangeBoundResult exchangeBound(const std::string& exchange=std::string(), const std::string& queue=std::string(), const std::string& bindingKey=std::string(), const FieldTable& arguments=FieldTable(), bool sync=true);
    
    QPID_CLIENT_EXTERN void queueDeclare(const std::string& queue=std::string(), const std::string& alternateExchange=std::string(), bool passive=false, bool durable=false, bool exclusive=false, bool autoDelete=false, const FieldTable& arguments=FieldTable(), bool sync=true);
    
    QPID_CLIENT_EXTERN void queueDelete(const std::string& queue=std::string(), bool ifUnused=false, bool ifEmpty=false, bool sync=true);
    
    QPID_CLIENT_EXTERN void queuePurge(const std::string& queue=std::string(), bool sync=true);
    
    QPID_CLIENT_EXTERN qpid::framing::QueueQueryResult queueQuery(const std::string& queue=std::string(), bool sync=true);
};

}}} // namespace qpid::client::no_keyword

#endif  /*!QPID_CLIENT_NO_KEYWORD_SESSION0_10_H*/
