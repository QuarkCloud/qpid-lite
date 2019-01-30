#ifndef QPID_DRIVER_ASYNCSESSION0_10_H
#define QPID_DRIVER_ASYNCSESSION0_10_H 1
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


#include "qpid/driver/SessionBase0_10.h"
#include "qpid/driver/Compile.h"
namespace qpid {
	namespace driver {

		/**
		 * AMQP 0-10 asynchronous session API.
		 */
		class AsyncSession0_10 : public SessionBase0_10
		{
		public:

			QPID_DRIVER_EXTERN AsyncSession0_10();
			QPID_DRIVER_INLINE_EXTERN AsyncSession0_10(const SessionBase0_10& other);
			QPID_DRIVER_INLINE_EXTERN AsyncSession0_10& operator=(const SessionBase0_10& other);

			QPID_DRIVER_EXTERN Completion executionSync(bool sync = false);

			QPID_DRIVER_EXTERN Completion executionResult(const SequenceNumber& commandId = SequenceNumber(), 
				const std::string& value = std::string(), bool sync = false);

			QPID_DRIVER_EXTERN Completion executionException(uint16_t errorCode = 0, 
				const SequenceNumber& commandId = SequenceNumber(), 
				uint8_t classCode = 0, uint8_t commandCode = 0, uint8_t fieldIndex = 0, 
				const std::string& description = std::string(), const FieldTable& errorInfo = FieldTable(), 
				bool sync = false);

			QPID_DRIVER_EXTERN Completion messageTransfer(const std::string& destination = std::string(), 
				uint8_t acceptMode = 1, uint8_t acquireMode = 0, const Message& content = Message(std::string()), 
				bool sync = false);

			QPID_DRIVER_EXTERN Completion messageAccept(const SequenceSet& transfers = SequenceSet(), bool sync = false);

			QPID_DRIVER_EXTERN Completion messageReject(const SequenceSet& transfers = SequenceSet(), uint16_t code = 0, 
				const std::string& text = std::string(), bool sync = false);

			QPID_DRIVER_EXTERN Completion messageRelease(const SequenceSet& transfers = SequenceSet(), bool setRedelivered = false, bool sync = false);

			QPID_DRIVER_EXTERN TypedResult<qpid::framing::MessageAcquireResult> messageAcquire(const SequenceSet& transfers = SequenceSet(), bool sync = false);

			QPID_DRIVER_EXTERN TypedResult<qpid::framing::MessageResumeResult> messageResume(const std::string& destination = std::string(), 
				const std::string& resumeId = std::string(), bool sync = false);

			QPID_DRIVER_EXTERN Completion messageSubscribe(const std::string& queue = std::string(), 
				const std::string& destination = std::string(), 
				uint8_t acceptMode = 0, uint8_t acquireMode = 0, bool exclusive = false, 
				const std::string& resumeId = std::string(), uint64_t resumeTtl = 0, 
				const FieldTable& arguments = FieldTable(), bool sync = false);

			QPID_DRIVER_EXTERN Completion messageCancel(const std::string& destination = std::string(), bool sync = false);

			QPID_DRIVER_EXTERN Completion messageSetFlowMode(const std::string& destination = std::string(), 
				uint8_t flowMode = 0, 
				bool sync = false);

			QPID_DRIVER_EXTERN Completion messageFlow(const std::string& destination = std::string(), uint8_t unit = 0, 
				uint32_t value = 0, bool sync = false);

			QPID_DRIVER_EXTERN Completion messageFlush(const std::string& destination = std::string(), bool sync = false);

			QPID_DRIVER_EXTERN Completion messageStop(const std::string& destination = std::string(), bool sync = false);

			QPID_DRIVER_EXTERN Completion txSelect(bool sync = false);

			QPID_DRIVER_EXTERN Completion txCommit(bool sync = false);

			QPID_DRIVER_EXTERN Completion txRollback(bool sync = false);

			QPID_DRIVER_EXTERN Completion dtxSelect(bool sync = false);

			QPID_DRIVER_EXTERN TypedResult<qpid::framing::XaResult> dtxStart(const Xid& xid = Xid(), bool join = false, 
				bool resume = false, bool sync = false);

			QPID_DRIVER_EXTERN TypedResult<qpid::framing::XaResult> dtxEnd(const Xid& xid = Xid(), bool fail = false, 
				bool suspend = false, bool sync = false);

			QPID_DRIVER_EXTERN TypedResult<qpid::framing::XaResult> dtxCommit(const Xid& xid = Xid(), bool onePhase = false, 
				bool sync = false);

			QPID_DRIVER_EXTERN Completion dtxForget(const Xid& xid = Xid(), bool sync = false);

			QPID_DRIVER_EXTERN TypedResult<qpid::framing::DtxGetTimeoutResult> dtxGetTimeout(const Xid& xid = Xid(), 
				bool sync = false);

			QPID_DRIVER_EXTERN TypedResult<qpid::framing::XaResult> dtxPrepare(const Xid& xid = Xid(), bool sync = false);

			QPID_DRIVER_EXTERN TypedResult<qpid::framing::DtxRecoverResult> dtxRecover(bool sync = false);

			QPID_DRIVER_EXTERN TypedResult<qpid::framing::XaResult> dtxRollback(const Xid& xid = Xid(), bool sync = false);

			QPID_DRIVER_EXTERN Completion dtxSetTimeout(const Xid& xid = Xid(), uint32_t timeout = 0, bool sync = false);

			QPID_DRIVER_EXTERN Completion exchangeDeclare(const std::string& exchange = std::string(), 
				const std::string& type = std::string(), const std::string& alternateExchange = std::string(), 
				bool passive = false, bool durable = false, bool autoDelete = false, 
				const FieldTable& arguments = FieldTable(), bool sync = false);

			QPID_DRIVER_EXTERN Completion exchangeDelete(const std::string& exchange = std::string(), bool ifUnused = false, 
				bool sync = false);

			QPID_DRIVER_EXTERN TypedResult<qpid::framing::ExchangeQueryResult> exchangeQuery(
				const std::string& name = std::string(), bool sync = false);

			QPID_DRIVER_EXTERN Completion exchangeBind(const std::string& queue = std::string(), 
				const std::string& exchange = std::string(), const std::string& bindingKey = std::string(), 
				const FieldTable& arguments = FieldTable(), bool sync = false);

			QPID_DRIVER_EXTERN Completion exchangeUnbind(const std::string& queue = std::string(), 
				const std::string& exchange = std::string(), const std::string& bindingKey = std::string(), 
				bool sync = false);

			QPID_DRIVER_EXTERN TypedResult<qpid::framing::ExchangeBoundResult> exchangeBound(
				const std::string& exchange = std::string(), const std::string& queue = std::string(), 
				const std::string& bindingKey = std::string(), const FieldTable& arguments = FieldTable(), 
				bool sync = false);

			QPID_DRIVER_EXTERN Completion queueDeclare(const std::string& queue = std::string(), 
				const std::string& alternateExchange = std::string(), bool passive = false, 
				bool durable = false, bool exclusive = false, bool autoDelete = false, 
				const FieldTable& arguments = FieldTable(), bool sync = false);

			QPID_DRIVER_EXTERN Completion queueDelete(const std::string& queue = std::string(), bool ifUnused = false, 
				bool ifEmpty = false, bool sync = false);

			QPID_DRIVER_EXTERN Completion queuePurge(const std::string& queue = std::string(), bool sync = false);

			QPID_DRIVER_EXTERN TypedResult<qpid::framing::QueueQueryResult> queueQuery(const std::string& queue = std::string(), 
				bool sync = false);
		};

		/** Conversion to AsyncSession0_10 from another session type */
		inline AsyncSession0_10 async(const SessionBase0_10& other) { return (other); }
	}
}// namespace qpid::driver

#endif  /*!QPID_DRIVER_ASYNCSESSION0_10_H*/
