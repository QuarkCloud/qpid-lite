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
#include "qpid/driver/SessionBase.h"
#include "qpid/driver/Connection.h"
#include "qpid/driver/ConnectionAccess.h"
#include "qpid/driver/SessionImpl.h"
#include "qpid/driver/Future.h"
#include "qpid/framing/all_method_bodies.h"

namespace qpid {
namespace driver {

using namespace framing;

SessionBase::SessionBase() {}
SessionBase::~SessionBase() {}

void SessionBase::close()
{ 
    if (impl) impl->close(); 
}

void SessionBase::flush()
{
    impl->sendFlush();
}

void SessionBase::sync()
{
    ExecutionSyncBody b;
    b.setSync(true);
    impl->send(b).wait(*impl);
}

void SessionBase::markCompleted(const framing::SequenceSet& ids, bool notifyPeer)
{
    impl->markCompleted(ids, notifyPeer);
}

void SessionBase::markCompleted(const framing::SequenceNumber& id, bool cumulative, bool notifyPeer)
{
    impl->markCompleted(id, cumulative, notifyPeer);
}

void SessionBase::sendCompletion()
{
    impl->sendCompletion();
}

uint16_t SessionBase::getChannel() const { return impl->getChannel(); }

void SessionBase::suspend() { impl->suspend(); }
void SessionBase::resume(Connection c) { impl->resume(c.impl); }
uint32_t SessionBase::timeout(uint32_t seconds) { return impl->setTimeout(seconds); }

SessionId SessionBase::getId() const { return impl->getId(); }

bool SessionBase::isValid() const { return !!impl; }

Connection SessionBase::getConnection()
{
    Connection c;
    ConnectionAccess::setImpl(c, impl->getConnection());
    return c;
}

}} // namespace qpid::driver
