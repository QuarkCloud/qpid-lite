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
#include "qpid/driver/LocalQueue.h"
#include "qpid/driver/LocalQueueImpl.h"
#include "qpid/driver/MessageImpl.h"
#include "qpid/driver/PrivateImplRef.h"
#include "qpid/driver/SubscriptionImpl.h"

#include "qpid/framing/FrameSet.h"
#include "qpid/framing/MessageTransferBody.h"
#include "qpid/framing/reply_exceptions.h"

#include "qpid/sys/Exception.h"


namespace qpid {
namespace driver {

using namespace framing;

typedef PrivateImplRef<LocalQueue> PI;

LocalQueue::LocalQueue() { PI::ctor(*this, new LocalQueueImpl()); }
LocalQueue::LocalQueue(const LocalQueue& x) : Handle<LocalQueueImpl>() { PI::copy(*this, x); }
LocalQueue::~LocalQueue() { PI::dtor(*this); }
LocalQueue& LocalQueue::operator=(const LocalQueue& x) { return PI::assign(*this, x); }

Message LocalQueue::pop(sys::NanoDuration timeout) { return impl->pop(timeout); }

Message LocalQueue::get(sys::NanoDuration timeout) { return impl->get(timeout); }

bool LocalQueue::get(Message& result, sys::NanoDuration timeout) { return impl->get(result, timeout); }

bool LocalQueue::empty() const { return impl->empty(); }
size_t LocalQueue::size() const { return impl->size(); }

}} // namespace qpid::driver
