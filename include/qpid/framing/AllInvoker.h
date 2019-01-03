#ifndef QPID_FRAMING_ALL_INVOKER_H
#define QPID_FRAMING_ALL_INVOKER_H 1
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


#include "qpid/framing/AMQP_AllOperations.h"
#include "qpid/framing/Invoker.h"
#include "qpid/framing/Compile.h"

namespace qpid {
namespace framing {


class QPID_FRAMING_CLASS_EXTERN AMQP_AllOperations::Invoker:
    public qpid::framing::Invoker
{
    AMQP_AllOperations& target;
  public:
    Invoker(AMQP_AllOperations& target_) : target(target_) {}
    using MethodBodyDefaultVisitor::visit;
    QPID_FRAMING_EXTERN void visit(const ConnectionStartBody& body);
    QPID_FRAMING_EXTERN void visit(const ConnectionStartOkBody& body);
    QPID_FRAMING_EXTERN void visit(const ConnectionSecureBody& body);
    QPID_FRAMING_EXTERN void visit(const ConnectionSecureOkBody& body);
    QPID_FRAMING_EXTERN void visit(const ConnectionTuneBody& body);
    QPID_FRAMING_EXTERN void visit(const ConnectionTuneOkBody& body);
    QPID_FRAMING_EXTERN void visit(const ConnectionOpenBody& body);
    QPID_FRAMING_EXTERN void visit(const ConnectionOpenOkBody& body);
    QPID_FRAMING_EXTERN void visit(const ConnectionRedirectBody& body);
    QPID_FRAMING_EXTERN void visit(const ConnectionHeartbeatBody& body);
    QPID_FRAMING_EXTERN void visit(const ConnectionCloseBody& body);
    QPID_FRAMING_EXTERN void visit(const ConnectionCloseOkBody& body);
    QPID_FRAMING_EXTERN void visit(const SessionAttachBody& body);
    QPID_FRAMING_EXTERN void visit(const SessionAttachedBody& body);
    QPID_FRAMING_EXTERN void visit(const SessionDetachBody& body);
    QPID_FRAMING_EXTERN void visit(const SessionDetachedBody& body);
    QPID_FRAMING_EXTERN void visit(const SessionRequestTimeoutBody& body);
    QPID_FRAMING_EXTERN void visit(const SessionTimeoutBody& body);
    QPID_FRAMING_EXTERN void visit(const SessionCommandPointBody& body);
    QPID_FRAMING_EXTERN void visit(const SessionExpectedBody& body);
    QPID_FRAMING_EXTERN void visit(const SessionConfirmedBody& body);
    QPID_FRAMING_EXTERN void visit(const SessionCompletedBody& body);
    QPID_FRAMING_EXTERN void visit(const SessionKnownCompletedBody& body);
    QPID_FRAMING_EXTERN void visit(const SessionFlushBody& body);
    QPID_FRAMING_EXTERN void visit(const SessionGapBody& body);
    QPID_FRAMING_EXTERN void visit(const ExecutionSyncBody& body);
    QPID_FRAMING_EXTERN void visit(const ExecutionResultBody& body);
    QPID_FRAMING_EXTERN void visit(const ExecutionExceptionBody& body);
    QPID_FRAMING_EXTERN void visit(const MessageAcceptBody& body);
    QPID_FRAMING_EXTERN void visit(const MessageRejectBody& body);
    QPID_FRAMING_EXTERN void visit(const MessageReleaseBody& body);
    QPID_FRAMING_EXTERN void visit(const MessageAcquireBody& body);
    QPID_FRAMING_EXTERN void visit(const MessageResumeBody& body);
    QPID_FRAMING_EXTERN void visit(const MessageSubscribeBody& body);
    QPID_FRAMING_EXTERN void visit(const MessageCancelBody& body);
    QPID_FRAMING_EXTERN void visit(const MessageSetFlowModeBody& body);
    QPID_FRAMING_EXTERN void visit(const MessageFlowBody& body);
    QPID_FRAMING_EXTERN void visit(const MessageFlushBody& body);
    QPID_FRAMING_EXTERN void visit(const MessageStopBody& body);
    QPID_FRAMING_EXTERN void visit(const TxSelectBody& body);
    QPID_FRAMING_EXTERN void visit(const TxCommitBody& body);
    QPID_FRAMING_EXTERN void visit(const TxRollbackBody& body);
    QPID_FRAMING_EXTERN void visit(const DtxSelectBody& body);
    QPID_FRAMING_EXTERN void visit(const DtxStartBody& body);
    QPID_FRAMING_EXTERN void visit(const DtxEndBody& body);
    QPID_FRAMING_EXTERN void visit(const DtxCommitBody& body);
    QPID_FRAMING_EXTERN void visit(const DtxForgetBody& body);
    QPID_FRAMING_EXTERN void visit(const DtxGetTimeoutBody& body);
    QPID_FRAMING_EXTERN void visit(const DtxPrepareBody& body);
    QPID_FRAMING_EXTERN void visit(const DtxRecoverBody& body);
    QPID_FRAMING_EXTERN void visit(const DtxRollbackBody& body);
    QPID_FRAMING_EXTERN void visit(const DtxSetTimeoutBody& body);
    QPID_FRAMING_EXTERN void visit(const ExchangeDeclareBody& body);
    QPID_FRAMING_EXTERN void visit(const ExchangeDeleteBody& body);
    QPID_FRAMING_EXTERN void visit(const ExchangeQueryBody& body);
    QPID_FRAMING_EXTERN void visit(const ExchangeBindBody& body);
    QPID_FRAMING_EXTERN void visit(const ExchangeUnbindBody& body);
    QPID_FRAMING_EXTERN void visit(const ExchangeBoundBody& body);
    QPID_FRAMING_EXTERN void visit(const QueueDeclareBody& body);
    QPID_FRAMING_EXTERN void visit(const QueueDeleteBody& body);
    QPID_FRAMING_EXTERN void visit(const QueuePurgeBody& body);
    QPID_FRAMING_EXTERN void visit(const QueueQueryBody& body);
    QPID_FRAMING_EXTERN void visit(const FileQosBody& body);
    QPID_FRAMING_EXTERN void visit(const FileQosOkBody& body);
    QPID_FRAMING_EXTERN void visit(const FileConsumeBody& body);
    QPID_FRAMING_EXTERN void visit(const FileConsumeOkBody& body);
    QPID_FRAMING_EXTERN void visit(const FileCancelBody& body);
    QPID_FRAMING_EXTERN void visit(const FileOpenBody& body);
    QPID_FRAMING_EXTERN void visit(const FileOpenOkBody& body);
    QPID_FRAMING_EXTERN void visit(const FilePublishBody& body);
    QPID_FRAMING_EXTERN void visit(const FileDeliverBody& body);
    QPID_FRAMING_EXTERN void visit(const FileAckBody& body);
    QPID_FRAMING_EXTERN void visit(const FileRejectBody& body);
    QPID_FRAMING_EXTERN void visit(const StreamQosBody& body);
    QPID_FRAMING_EXTERN void visit(const StreamQosOkBody& body);
    QPID_FRAMING_EXTERN void visit(const StreamConsumeBody& body);
    QPID_FRAMING_EXTERN void visit(const StreamConsumeOkBody& body);
    QPID_FRAMING_EXTERN void visit(const StreamCancelBody& body);
};

class QPID_FRAMING_CLASS_EXTERN AMQP_AllOperations::ConnectionHandler::Invoker:
    public qpid::framing::Invoker
{
    AMQP_AllOperations::ConnectionHandler& target;
  public:
    Invoker(AMQP_AllOperations::ConnectionHandler& target_) : target(target_) {}
    using MethodBodyDefaultVisitor::visit;
    QPID_FRAMING_EXTERN void visit(const ConnectionStartBody& body);
    QPID_FRAMING_EXTERN void visit(const ConnectionStartOkBody& body);
    QPID_FRAMING_EXTERN void visit(const ConnectionSecureBody& body);
    QPID_FRAMING_EXTERN void visit(const ConnectionSecureOkBody& body);
    QPID_FRAMING_EXTERN void visit(const ConnectionTuneBody& body);
    QPID_FRAMING_EXTERN void visit(const ConnectionTuneOkBody& body);
    QPID_FRAMING_EXTERN void visit(const ConnectionOpenBody& body);
    QPID_FRAMING_EXTERN void visit(const ConnectionOpenOkBody& body);
    QPID_FRAMING_EXTERN void visit(const ConnectionRedirectBody& body);
    QPID_FRAMING_EXTERN void visit(const ConnectionHeartbeatBody& body);
    QPID_FRAMING_EXTERN void visit(const ConnectionCloseBody& body);
    QPID_FRAMING_EXTERN void visit(const ConnectionCloseOkBody& body);
};

class QPID_FRAMING_CLASS_EXTERN AMQP_AllOperations::SessionHandler::Invoker:
    public qpid::framing::Invoker
{
    AMQP_AllOperations::SessionHandler& target;
  public:
    Invoker(AMQP_AllOperations::SessionHandler& target_) : target(target_) {}
    using MethodBodyDefaultVisitor::visit;
    QPID_FRAMING_EXTERN void visit(const SessionAttachBody& body);
    QPID_FRAMING_EXTERN void visit(const SessionAttachedBody& body);
    QPID_FRAMING_EXTERN void visit(const SessionDetachBody& body);
    QPID_FRAMING_EXTERN void visit(const SessionDetachedBody& body);
    QPID_FRAMING_EXTERN void visit(const SessionRequestTimeoutBody& body);
    QPID_FRAMING_EXTERN void visit(const SessionTimeoutBody& body);
    QPID_FRAMING_EXTERN void visit(const SessionCommandPointBody& body);
    QPID_FRAMING_EXTERN void visit(const SessionExpectedBody& body);
    QPID_FRAMING_EXTERN void visit(const SessionConfirmedBody& body);
    QPID_FRAMING_EXTERN void visit(const SessionCompletedBody& body);
    QPID_FRAMING_EXTERN void visit(const SessionKnownCompletedBody& body);
    QPID_FRAMING_EXTERN void visit(const SessionFlushBody& body);
    QPID_FRAMING_EXTERN void visit(const SessionGapBody& body);
};

class QPID_FRAMING_CLASS_EXTERN AMQP_AllOperations::ExecutionHandler::Invoker:
    public qpid::framing::Invoker
{
    AMQP_AllOperations::ExecutionHandler& target;
  public:
    Invoker(AMQP_AllOperations::ExecutionHandler& target_) : target(target_) {}
    using MethodBodyDefaultVisitor::visit;
    QPID_FRAMING_EXTERN void visit(const ExecutionSyncBody& body);
    QPID_FRAMING_EXTERN void visit(const ExecutionResultBody& body);
    QPID_FRAMING_EXTERN void visit(const ExecutionExceptionBody& body);
};

class QPID_FRAMING_CLASS_EXTERN AMQP_AllOperations::MessageHandler::Invoker:
    public qpid::framing::Invoker
{
    AMQP_AllOperations::MessageHandler& target;
  public:
    Invoker(AMQP_AllOperations::MessageHandler& target_) : target(target_) {}
    using MethodBodyDefaultVisitor::visit;
    QPID_FRAMING_EXTERN void visit(const MessageAcceptBody& body);
    QPID_FRAMING_EXTERN void visit(const MessageRejectBody& body);
    QPID_FRAMING_EXTERN void visit(const MessageReleaseBody& body);
    QPID_FRAMING_EXTERN void visit(const MessageAcquireBody& body);
    QPID_FRAMING_EXTERN void visit(const MessageResumeBody& body);
    QPID_FRAMING_EXTERN void visit(const MessageSubscribeBody& body);
    QPID_FRAMING_EXTERN void visit(const MessageCancelBody& body);
    QPID_FRAMING_EXTERN void visit(const MessageSetFlowModeBody& body);
    QPID_FRAMING_EXTERN void visit(const MessageFlowBody& body);
    QPID_FRAMING_EXTERN void visit(const MessageFlushBody& body);
    QPID_FRAMING_EXTERN void visit(const MessageStopBody& body);
};

class QPID_FRAMING_CLASS_EXTERN AMQP_AllOperations::TxHandler::Invoker:
    public qpid::framing::Invoker
{
    AMQP_AllOperations::TxHandler& target;
  public:
    Invoker(AMQP_AllOperations::TxHandler& target_) : target(target_) {}
    using MethodBodyDefaultVisitor::visit;
    QPID_FRAMING_EXTERN void visit(const TxSelectBody& body);
    QPID_FRAMING_EXTERN void visit(const TxCommitBody& body);
    QPID_FRAMING_EXTERN void visit(const TxRollbackBody& body);
};

class QPID_FRAMING_CLASS_EXTERN AMQP_AllOperations::DtxHandler::Invoker:
    public qpid::framing::Invoker
{
    AMQP_AllOperations::DtxHandler& target;
  public:
    Invoker(AMQP_AllOperations::DtxHandler& target_) : target(target_) {}
    using MethodBodyDefaultVisitor::visit;
    QPID_FRAMING_EXTERN void visit(const DtxSelectBody& body);
    QPID_FRAMING_EXTERN void visit(const DtxStartBody& body);
    QPID_FRAMING_EXTERN void visit(const DtxEndBody& body);
    QPID_FRAMING_EXTERN void visit(const DtxCommitBody& body);
    QPID_FRAMING_EXTERN void visit(const DtxForgetBody& body);
    QPID_FRAMING_EXTERN void visit(const DtxGetTimeoutBody& body);
    QPID_FRAMING_EXTERN void visit(const DtxPrepareBody& body);
    QPID_FRAMING_EXTERN void visit(const DtxRecoverBody& body);
    QPID_FRAMING_EXTERN void visit(const DtxRollbackBody& body);
    QPID_FRAMING_EXTERN void visit(const DtxSetTimeoutBody& body);
};

class QPID_FRAMING_CLASS_EXTERN AMQP_AllOperations::ExchangeHandler::Invoker:
    public qpid::framing::Invoker
{
    AMQP_AllOperations::ExchangeHandler& target;
  public:
    Invoker(AMQP_AllOperations::ExchangeHandler& target_) : target(target_) {}
    using MethodBodyDefaultVisitor::visit;
    QPID_FRAMING_EXTERN void visit(const ExchangeDeclareBody& body);
    QPID_FRAMING_EXTERN void visit(const ExchangeDeleteBody& body);
    QPID_FRAMING_EXTERN void visit(const ExchangeQueryBody& body);
    QPID_FRAMING_EXTERN void visit(const ExchangeBindBody& body);
    QPID_FRAMING_EXTERN void visit(const ExchangeUnbindBody& body);
    QPID_FRAMING_EXTERN void visit(const ExchangeBoundBody& body);
};

class QPID_FRAMING_CLASS_EXTERN AMQP_AllOperations::QueueHandler::Invoker:
    public qpid::framing::Invoker
{
    AMQP_AllOperations::QueueHandler& target;
  public:
    Invoker(AMQP_AllOperations::QueueHandler& target_) : target(target_) {}
    using MethodBodyDefaultVisitor::visit;
    QPID_FRAMING_EXTERN void visit(const QueueDeclareBody& body);
    QPID_FRAMING_EXTERN void visit(const QueueDeleteBody& body);
    QPID_FRAMING_EXTERN void visit(const QueuePurgeBody& body);
    QPID_FRAMING_EXTERN void visit(const QueueQueryBody& body);
};

class QPID_FRAMING_CLASS_EXTERN AMQP_AllOperations::FileHandler::Invoker:
    public qpid::framing::Invoker
{
    AMQP_AllOperations::FileHandler& target;
  public:
    Invoker(AMQP_AllOperations::FileHandler& target_) : target(target_) {}
    using MethodBodyDefaultVisitor::visit;
    QPID_FRAMING_EXTERN void visit(const FileQosBody& body);
    QPID_FRAMING_EXTERN void visit(const FileQosOkBody& body);
    QPID_FRAMING_EXTERN void visit(const FileConsumeBody& body);
    QPID_FRAMING_EXTERN void visit(const FileConsumeOkBody& body);
    QPID_FRAMING_EXTERN void visit(const FileCancelBody& body);
    QPID_FRAMING_EXTERN void visit(const FileOpenBody& body);
    QPID_FRAMING_EXTERN void visit(const FileOpenOkBody& body);
    QPID_FRAMING_EXTERN void visit(const FilePublishBody& body);
    QPID_FRAMING_EXTERN void visit(const FileDeliverBody& body);
    QPID_FRAMING_EXTERN void visit(const FileAckBody& body);
    QPID_FRAMING_EXTERN void visit(const FileRejectBody& body);
};

class QPID_FRAMING_CLASS_EXTERN AMQP_AllOperations::StreamHandler::Invoker:
    public qpid::framing::Invoker
{
    AMQP_AllOperations::StreamHandler& target;
  public:
    Invoker(AMQP_AllOperations::StreamHandler& target_) : target(target_) {}
    using MethodBodyDefaultVisitor::visit;
    QPID_FRAMING_EXTERN void visit(const StreamQosBody& body);
    QPID_FRAMING_EXTERN void visit(const StreamQosOkBody& body);
    QPID_FRAMING_EXTERN void visit(const StreamConsumeBody& body);
    QPID_FRAMING_EXTERN void visit(const StreamConsumeOkBody& body);
    QPID_FRAMING_EXTERN void visit(const StreamCancelBody& body);
};

}} // namespace qpid::framing

#endif  /*!QPID_FRAMING_ALL_INVOKER_H*/
