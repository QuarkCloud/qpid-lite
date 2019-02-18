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


#include "qpid/driver/Session.h"
#include "qpid/framing/all_method_bodies.h"
#include "qpid/driver/SessionImpl.h"
#include "qpid/driver/MessageImpl.h"
#include "qpid/driver/PrivateImplRef.h"
#include "qpid/driver/CompletionImpl.h"
#include <boost/intrusive_ptr.hpp>

namespace qpid {
	namespace driver {

		using namespace framing;

		void Session::executionSync(bool sync) {
			ExecutionSyncBody body(ProtocolVersion(0, 10));
			body.setSync(sync);
			Completion(new CompletionImpl(impl->send(body), impl)).wait();
		}

		void Session::executionResult(const SequenceNumber& commandId, const std::string& value, bool sync) {
			ExecutionResultBody body(ProtocolVersion(0, 10), commandId, value);
			body.setSync(sync);
			Completion(new CompletionImpl(impl->send(body), impl)).wait();
		}

		void Session::executionException(uint16_t errorCode, const SequenceNumber& commandId, uint8_t classCode, uint8_t commandCode, uint8_t fieldIndex, const std::string& description, const FieldTable& errorInfo, bool sync) {
			ExecutionExceptionBody body(ProtocolVersion(0, 10), errorCode, commandId, classCode, commandCode, fieldIndex, description, errorInfo);
			body.setSync(sync);
			Completion(new CompletionImpl(impl->send(body), impl)).wait();
		}

		void Session::messageTransfer(const std::string& destination, uint8_t acceptMode, uint8_t acquireMode, const Message& content, bool sync) {
			MessageTransferBody body(ProtocolVersion(0, 10), destination, acceptMode, acquireMode);
			body.setSync(sync);
			Completion(new CompletionImpl(impl->send(body, *MessageImpl::get(content)), impl)).wait();
		}

		void Session::messageAccept(const SequenceSet& transfers, bool sync) {
			MessageAcceptBody body(ProtocolVersion(0, 10), transfers);
			body.setSync(sync);
			Completion(new CompletionImpl(impl->send(body), impl)).wait();
		}

		void Session::messageReject(const SequenceSet& transfers, uint16_t code, const std::string& text, bool sync) {
			MessageRejectBody body(ProtocolVersion(0, 10), transfers, code, text);
			body.setSync(sync);
			Completion(new CompletionImpl(impl->send(body), impl)).wait();
		}

		void Session::messageRelease(const SequenceSet& transfers, bool setRedelivered, bool sync) {
			MessageReleaseBody body(ProtocolVersion(0, 10), transfers, setRedelivered);
			body.setSync(sync);
			Completion(new CompletionImpl(impl->send(body), impl)).wait();
		}

		qpid::framing::MessageAcquireResult Session::messageAcquire(const SequenceSet& transfers, bool sync) {
			MessageAcquireBody body(ProtocolVersion(0, 10), transfers);
			body.setSync(sync);
			return TypedResult<qpid::framing::MessageAcquireResult>(new CompletionImpl(impl->send(body), impl)).get();
		}

		qpid::framing::MessageResumeResult Session::messageResume(const std::string& destination, const std::string& resumeId, bool sync) {
			MessageResumeBody body(ProtocolVersion(0, 10), destination, resumeId);
			body.setSync(sync);
			return TypedResult<qpid::framing::MessageResumeResult>(new CompletionImpl(impl->send(body), impl)).get();
		}

		void Session::messageSubscribe(const std::string& queue, const std::string& destination, uint8_t acceptMode, uint8_t acquireMode, bool exclusive, const std::string& resumeId, uint64_t resumeTtl, const FieldTable& arguments, bool sync) {
			MessageSubscribeBody body(ProtocolVersion(0, 10), queue, destination, acceptMode, acquireMode, exclusive, resumeId, resumeTtl, arguments);
			body.setSync(sync);
			Completion(new CompletionImpl(impl->send(body), impl)).wait();
		}

		void Session::messageCancel(const std::string& destination, bool sync) {
			MessageCancelBody body(ProtocolVersion(0, 10), destination);
			body.setSync(sync);
			Completion(new CompletionImpl(impl->send(body), impl)).wait();
		}

		void Session::messageSetFlowMode(const std::string& destination, uint8_t flowMode, bool sync) {
			MessageSetFlowModeBody body(ProtocolVersion(0, 10), destination, flowMode);
			body.setSync(sync);
			Completion(new CompletionImpl(impl->send(body), impl)).wait();
		}

		void Session::messageFlow(const std::string& destination, uint8_t unit, uint32_t value, bool sync) {
			MessageFlowBody body(ProtocolVersion(0, 10), destination, unit, value);
			body.setSync(sync);
			Completion(new CompletionImpl(impl->send(body), impl)).wait();
		}

		void Session::messageFlush(const std::string& destination, bool sync) {
			MessageFlushBody body(ProtocolVersion(0, 10), destination);
			body.setSync(sync);
			Completion(new CompletionImpl(impl->send(body), impl)).wait();
		}

		void Session::messageStop(const std::string& destination, bool sync) {
			MessageStopBody body(ProtocolVersion(0, 10), destination);
			body.setSync(sync);
			Completion(new CompletionImpl(impl->send(body), impl)).wait();
		}

		void Session::txSelect(bool sync) {
			TxSelectBody body(ProtocolVersion(0, 10));
			body.setSync(sync);
			Completion(new CompletionImpl(impl->send(body), impl)).wait();
		}

		void Session::txCommit(bool sync) {
			TxCommitBody body(ProtocolVersion(0, 10));
			body.setSync(sync);
			Completion(new CompletionImpl(impl->send(body), impl)).wait();
		}

		void Session::txRollback(bool sync) {
			TxRollbackBody body(ProtocolVersion(0, 10));
			body.setSync(sync);
			Completion(new CompletionImpl(impl->send(body), impl)).wait();
		}

		void Session::dtxSelect(bool sync) {
			DtxSelectBody body(ProtocolVersion(0, 10));
			body.setSync(sync);
			Completion(new CompletionImpl(impl->send(body), impl)).wait();
		}

		qpid::framing::XaResult Session::dtxStart(const Xid& xid, bool join, bool resume, bool sync) {
			DtxStartBody body(ProtocolVersion(0, 10), xid, join, resume);
			body.setSync(sync);
			return TypedResult<qpid::framing::XaResult>(new CompletionImpl(impl->send(body), impl)).get();
		}

		qpid::framing::XaResult Session::dtxEnd(const Xid& xid, bool fail, bool suspend, bool sync) {
			DtxEndBody body(ProtocolVersion(0, 10), xid, fail, suspend);
			body.setSync(sync);
			return TypedResult<qpid::framing::XaResult>(new CompletionImpl(impl->send(body), impl)).get();
		}

		qpid::framing::XaResult Session::dtxCommit(const Xid& xid, bool onePhase, bool sync) {
			DtxCommitBody body(ProtocolVersion(0, 10), xid, onePhase);
			body.setSync(sync);
			return TypedResult<qpid::framing::XaResult>(new CompletionImpl(impl->send(body), impl)).get();
		}

		void Session::dtxForget(const Xid& xid, bool sync) {
			DtxForgetBody body(ProtocolVersion(0, 10), xid);
			body.setSync(sync);
			Completion(new CompletionImpl(impl->send(body), impl)).wait();
		}

		qpid::framing::DtxGetTimeoutResult Session::dtxGetTimeout(const Xid& xid, bool sync) {
			DtxGetTimeoutBody body(ProtocolVersion(0, 10), xid);
			body.setSync(sync);
			return TypedResult<qpid::framing::DtxGetTimeoutResult>(new CompletionImpl(impl->send(body), impl)).get();
		}

		qpid::framing::XaResult Session::dtxPrepare(const Xid& xid, bool sync) {
			DtxPrepareBody body(ProtocolVersion(0, 10), xid);
			body.setSync(sync);
			return TypedResult<qpid::framing::XaResult>(new CompletionImpl(impl->send(body), impl)).get();
		}

		qpid::framing::DtxRecoverResult Session::dtxRecover(bool sync) {
			DtxRecoverBody body(ProtocolVersion(0, 10));
			body.setSync(sync);
			return TypedResult<qpid::framing::DtxRecoverResult>(new CompletionImpl(impl->send(body), impl)).get();
		}

		qpid::framing::XaResult Session::dtxRollback(const Xid& xid, bool sync) {
			DtxRollbackBody body(ProtocolVersion(0, 10), xid);
			body.setSync(sync);
			return TypedResult<qpid::framing::XaResult>(new CompletionImpl(impl->send(body), impl)).get();
		}

		void Session::dtxSetTimeout(const Xid& xid, uint32_t timeout, bool sync) {
			DtxSetTimeoutBody body(ProtocolVersion(0, 10), xid, timeout);
			body.setSync(sync);
			Completion(new CompletionImpl(impl->send(body), impl)).wait();
		}

		void Session::exchangeDeclare(const std::string& exchange, const std::string& type, const std::string& alternateExchange, bool passive, bool durable, bool autoDelete, const FieldTable& arguments, bool sync) {
			ExchangeDeclareBody body(ProtocolVersion(0, 10), exchange, type, alternateExchange, passive, durable, autoDelete, arguments);
			body.setSync(sync);
			Completion(new CompletionImpl(impl->send(body), impl)).wait();
		}

		void Session::exchangeDelete(const std::string& exchange, bool ifUnused, bool sync) {
			ExchangeDeleteBody body(ProtocolVersion(0, 10), exchange, ifUnused);
			body.setSync(sync);
			Completion(new CompletionImpl(impl->send(body), impl)).wait();
		}

		qpid::framing::ExchangeQueryResult Session::exchangeQuery(const std::string& name, bool sync) {
			ExchangeQueryBody body(ProtocolVersion(0, 10), name);
			body.setSync(sync);
			return TypedResult<qpid::framing::ExchangeQueryResult>(new CompletionImpl(impl->send(body), impl)).get();
		}

		void Session::exchangeBind(const std::string& queue, const std::string& exchange, const std::string& bindingKey, const FieldTable& arguments, bool sync) {
			ExchangeBindBody body(ProtocolVersion(0, 10), queue, exchange, bindingKey, arguments);
			body.setSync(sync);
			Completion(new CompletionImpl(impl->send(body), impl)).wait();
		}

		void Session::exchangeUnbind(const std::string& queue, const std::string& exchange, const std::string& bindingKey, bool sync)
		{
			ExchangeUnbindBody body(ProtocolVersion(0, 10), queue, exchange, bindingKey);
			body.setSync(sync);
			Completion(new CompletionImpl(impl->send(body), impl)).wait();
		}

		qpid::framing::ExchangeBoundResult Session::exchangeBound(const std::string& exchange, const std::string& queue, const std::string& bindingKey, const FieldTable& arguments, bool sync) {
			ExchangeBoundBody body(ProtocolVersion(0, 10), exchange, queue, bindingKey, arguments);
			body.setSync(sync);
			return TypedResult<qpid::framing::ExchangeBoundResult>(new CompletionImpl(impl->send(body), impl)).get();
		}

		void Session::queueDeclare(const std::string& queue, const std::string& alternateExchange, bool passive, bool durable, bool exclusive, bool autoDelete, const FieldTable& arguments, bool sync) {
			QueueDeclareBody body(ProtocolVersion(0, 10), queue, alternateExchange, passive, durable, exclusive, autoDelete, arguments);
			body.setSync(sync);
			Completion(new CompletionImpl(impl->send(body), impl)).wait();
		}

		void Session::queueDelete(const std::string& queue, bool ifUnused, bool ifEmpty, bool sync) {
			QueueDeleteBody body(ProtocolVersion(0, 10), queue, ifUnused, ifEmpty);
			body.setSync(sync);
			Completion(new CompletionImpl(impl->send(body), impl)).wait();
		}

		void Session::queuePurge(const std::string& queue, bool sync) {
			QueuePurgeBody body(ProtocolVersion(0, 10), queue);
			body.setSync(sync);
			Completion(new CompletionImpl(impl->send(body), impl)).wait();
		}

		qpid::framing::QueueQueryResult Session::queueQuery(const std::string& queue, bool sync) {
			QueueQueryBody body(ProtocolVersion(0, 10), queue);
			body.setSync(sync);
			return TypedResult<qpid::framing::QueueQueryResult>(new CompletionImpl(impl->send(body), impl)).get();
		}

		Session::Session() {}
		Session::Session(const SessionBase& other) {
			*this = other;
		}
		Session& Session::operator=(const SessionBase& other) {
			impl = static_cast<const Session&>(other).impl;
			return *this;
		}

	}
}// namespace qpid::driver

