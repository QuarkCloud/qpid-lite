#ifndef QPID_FRAMING_METHOD_BODY_DEFAULT_VISITOR_H
#define QPID_FRAMING_METHOD_BODY_DEFAULT_VISITOR_H 1
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


#include "qpid/framing/MethodBodyConstVisitor.h"
#include "qpid/framing/Compile.h"

namespace qpid {
namespace framing {

class AMQMethodBody;
class QPID_FRAMING_CLASS_EXTERN MethodBodyDefaultVisitor:
    public MethodBodyConstVisitor
{
    public:
    virtual void defaultVisit(const AMQMethodBody&) = 0;
    QPID_FRAMING_EXTERN virtual void visit(const ConnectionStartBody&);
    QPID_FRAMING_EXTERN virtual void visit(const ConnectionStartOkBody&);
    QPID_FRAMING_EXTERN virtual void visit(const ConnectionSecureBody&);
    QPID_FRAMING_EXTERN virtual void visit(const ConnectionSecureOkBody&);
    QPID_FRAMING_EXTERN virtual void visit(const ConnectionTuneBody&);
    QPID_FRAMING_EXTERN virtual void visit(const ConnectionTuneOkBody&);
    QPID_FRAMING_EXTERN virtual void visit(const ConnectionOpenBody&);
    QPID_FRAMING_EXTERN virtual void visit(const ConnectionOpenOkBody&);
    QPID_FRAMING_EXTERN virtual void visit(const ConnectionRedirectBody&);
    QPID_FRAMING_EXTERN virtual void visit(const ConnectionHeartbeatBody&);
    QPID_FRAMING_EXTERN virtual void visit(const ConnectionCloseBody&);
    QPID_FRAMING_EXTERN virtual void visit(const ConnectionCloseOkBody&);
    QPID_FRAMING_EXTERN virtual void visit(const SessionAttachBody&);
    QPID_FRAMING_EXTERN virtual void visit(const SessionAttachedBody&);
    QPID_FRAMING_EXTERN virtual void visit(const SessionDetachBody&);
    QPID_FRAMING_EXTERN virtual void visit(const SessionDetachedBody&);
    QPID_FRAMING_EXTERN virtual void visit(const SessionRequestTimeoutBody&);
    QPID_FRAMING_EXTERN virtual void visit(const SessionTimeoutBody&);
    QPID_FRAMING_EXTERN virtual void visit(const SessionCommandPointBody&);
    QPID_FRAMING_EXTERN virtual void visit(const SessionExpectedBody&);
    QPID_FRAMING_EXTERN virtual void visit(const SessionConfirmedBody&);
    QPID_FRAMING_EXTERN virtual void visit(const SessionCompletedBody&);
    QPID_FRAMING_EXTERN virtual void visit(const SessionKnownCompletedBody&);
    QPID_FRAMING_EXTERN virtual void visit(const SessionFlushBody&);
    QPID_FRAMING_EXTERN virtual void visit(const SessionGapBody&);
    QPID_FRAMING_EXTERN virtual void visit(const ExecutionSyncBody&);
    QPID_FRAMING_EXTERN virtual void visit(const ExecutionResultBody&);
    QPID_FRAMING_EXTERN virtual void visit(const ExecutionExceptionBody&);
    QPID_FRAMING_EXTERN virtual void visit(const MessageTransferBody&);
    QPID_FRAMING_EXTERN virtual void visit(const MessageAcceptBody&);
    QPID_FRAMING_EXTERN virtual void visit(const MessageRejectBody&);
    QPID_FRAMING_EXTERN virtual void visit(const MessageReleaseBody&);
    QPID_FRAMING_EXTERN virtual void visit(const MessageAcquireBody&);
    QPID_FRAMING_EXTERN virtual void visit(const MessageResumeBody&);
    QPID_FRAMING_EXTERN virtual void visit(const MessageSubscribeBody&);
    QPID_FRAMING_EXTERN virtual void visit(const MessageCancelBody&);
    QPID_FRAMING_EXTERN virtual void visit(const MessageSetFlowModeBody&);
    QPID_FRAMING_EXTERN virtual void visit(const MessageFlowBody&);
    QPID_FRAMING_EXTERN virtual void visit(const MessageFlushBody&);
    QPID_FRAMING_EXTERN virtual void visit(const MessageStopBody&);
    QPID_FRAMING_EXTERN virtual void visit(const TxSelectBody&);
    QPID_FRAMING_EXTERN virtual void visit(const TxCommitBody&);
    QPID_FRAMING_EXTERN virtual void visit(const TxRollbackBody&);
    QPID_FRAMING_EXTERN virtual void visit(const DtxSelectBody&);
    QPID_FRAMING_EXTERN virtual void visit(const DtxStartBody&);
    QPID_FRAMING_EXTERN virtual void visit(const DtxEndBody&);
    QPID_FRAMING_EXTERN virtual void visit(const DtxCommitBody&);
    QPID_FRAMING_EXTERN virtual void visit(const DtxForgetBody&);
    QPID_FRAMING_EXTERN virtual void visit(const DtxGetTimeoutBody&);
    QPID_FRAMING_EXTERN virtual void visit(const DtxPrepareBody&);
    QPID_FRAMING_EXTERN virtual void visit(const DtxRecoverBody&);
    QPID_FRAMING_EXTERN virtual void visit(const DtxRollbackBody&);
    QPID_FRAMING_EXTERN virtual void visit(const DtxSetTimeoutBody&);
    QPID_FRAMING_EXTERN virtual void visit(const ExchangeDeclareBody&);
    QPID_FRAMING_EXTERN virtual void visit(const ExchangeDeleteBody&);
    QPID_FRAMING_EXTERN virtual void visit(const ExchangeQueryBody&);
    QPID_FRAMING_EXTERN virtual void visit(const ExchangeBindBody&);
    QPID_FRAMING_EXTERN virtual void visit(const ExchangeUnbindBody&);
    QPID_FRAMING_EXTERN virtual void visit(const ExchangeBoundBody&);
    QPID_FRAMING_EXTERN virtual void visit(const QueueDeclareBody&);
    QPID_FRAMING_EXTERN virtual void visit(const QueueDeleteBody&);
    QPID_FRAMING_EXTERN virtual void visit(const QueuePurgeBody&);
    QPID_FRAMING_EXTERN virtual void visit(const QueueQueryBody&);
    QPID_FRAMING_EXTERN virtual void visit(const FileQosBody&);
    QPID_FRAMING_EXTERN virtual void visit(const FileQosOkBody&);
    QPID_FRAMING_EXTERN virtual void visit(const FileConsumeBody&);
    QPID_FRAMING_EXTERN virtual void visit(const FileConsumeOkBody&);
    QPID_FRAMING_EXTERN virtual void visit(const FileCancelBody&);
    QPID_FRAMING_EXTERN virtual void visit(const FileOpenBody&);
    QPID_FRAMING_EXTERN virtual void visit(const FileOpenOkBody&);
    QPID_FRAMING_EXTERN virtual void visit(const FileStageBody&);
    QPID_FRAMING_EXTERN virtual void visit(const FilePublishBody&);
    QPID_FRAMING_EXTERN virtual void visit(const FileReturnBody&);
    QPID_FRAMING_EXTERN virtual void visit(const FileDeliverBody&);
    QPID_FRAMING_EXTERN virtual void visit(const FileAckBody&);
    QPID_FRAMING_EXTERN virtual void visit(const FileRejectBody&);
    QPID_FRAMING_EXTERN virtual void visit(const StreamQosBody&);
    QPID_FRAMING_EXTERN virtual void visit(const StreamQosOkBody&);
    QPID_FRAMING_EXTERN virtual void visit(const StreamConsumeBody&);
    QPID_FRAMING_EXTERN virtual void visit(const StreamConsumeOkBody&);
    QPID_FRAMING_EXTERN virtual void visit(const StreamCancelBody&);
    QPID_FRAMING_EXTERN virtual void visit(const StreamPublishBody&);
    QPID_FRAMING_EXTERN virtual void visit(const StreamReturnBody&);
    QPID_FRAMING_EXTERN virtual void visit(const StreamDeliverBody&);
};

}} // namespace qpid::framing

#endif  /*!QPID_FRAMING_METHOD_BODY_DEFAULT_VISITOR_H*/
