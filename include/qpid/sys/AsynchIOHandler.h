#ifndef QPID_SYS_ASYNCH_IO_HANDLER_H
#define QPID_SYS_ASYNCH_IO_HANDLER_H
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

#include "qpid/sys/OutputControl.h"
#include "qpid/sys/ConnectionCodec.h"
#include "qpid/sys/AtomicValue.h"
#include "qpid/sys/Mutex.h"
#include "qpid/sys/Compile.h"

#include <boost/intrusive_ptr.hpp>
#include <string>

namespace qpid {

namespace framing {
    class ProtocolInitiation;
}


namespace sys {

class AsynchIO;
struct AsynchIOBufferBase;
class Socket;
class Timer;
class TimerTask;

class AsynchIOHandler : public OutputControl {
    std::string identifier;
    AsynchIO* aio;
    ConnectionCodec::Factory* factory;
    ConnectionCodec* codec;
    bool readError;
    bool isClient;
    bool nodict;
    bool headerSent;
    boost::intrusive_ptr<sys::TimerTask> timeoutTimerTask;

    void write(const framing::ProtocolInitiation&);

  public:
    QPID_SYS_EXTERN AsynchIOHandler(const std::string& id, qpid::sys::ConnectionCodec::Factory* f, bool isClient, bool nodict);
	QPID_SYS_EXTERN ~AsynchIOHandler();
	QPID_SYS_EXTERN void init(AsynchIO* a, Timer& timer, uint32_t maxTime);

    // Output side
	QPID_SYS_EXTERN void abort();
	QPID_SYS_EXTERN void connectionEstablished();
	QPID_SYS_EXTERN void activateOutput();

    // Input side
	QPID_SYS_EXTERN void readbuff(AsynchIO& aio, AsynchIOBufferBase* buff);
	QPID_SYS_EXTERN void eof(AsynchIO& aio);
	QPID_SYS_EXTERN void disconnect(AsynchIO& aio);

    // Notifications
	QPID_SYS_EXTERN void nobuffs(AsynchIO& aio);
	QPID_SYS_EXTERN void idle(AsynchIO& aio);
	QPID_SYS_EXTERN void closedSocket(AsynchIO& aio, const Socket& s);
};

}} // namespace qpid::sys

#endif // QPID_SYS_ASYNCH_IO_HANDLER_H
