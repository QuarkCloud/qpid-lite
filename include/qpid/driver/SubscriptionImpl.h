#ifndef QPID_DRIVER_SUBSCRIPTION_IMPL_H
#define QPID_DRIVER_SUBSCRIPTION_IMPL_H 1

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

#include "qpid/driver/SubscriptionSettings.h"
#include "qpid/driver/SubscriptionManager.h"
#include "qpid/driver/Session.h"
#include "qpid/driver/MessageListener.h"
#include "qpid/driver/Demux.h"
#include "qpid/framing/enum.h"
#include "qpid/framing/SequenceSet.h"
#include "qpid/sys/Mutex.h"
#include "qpid/sys/RefCounted.h"
#include "qpid/driver/Compile.h"
#include <memory>

namespace qpid {
namespace driver {

class SubscriptionManager;
class SubscriptionManagerImpl;

class SubscriptionImpl : public sys::RefCounted, public MessageListener {
  public:
    QPID_DRIVER_EXTERN SubscriptionImpl(SubscriptionManager, const std::string& queue,
        const SubscriptionSettings&, const std::string& name, MessageListener* =0);
    
    /** The name of the subsctription, used as the "destination" for messages from the broker.
     * Usually the same as the queue name but can be set differently.
     */
    QPID_DRIVER_EXTERN std::string getName() const;

    /** Name of the queue this subscription subscribes to */
    QPID_DRIVER_EXTERN std::string getQueue() const;

    /** Get the flow control and acknowledgement settings for this subscription */
    QPID_DRIVER_EXTERN const SubscriptionSettings& getSettings() const;

    /** Set the flow control parameters */
    QPID_DRIVER_EXTERN void setFlowControl(const FlowControl&);

    /** Automatically acknowledge (acquire and accept) batches of n messages.
     * You can disable auto-acknowledgement by setting n=0, and use acquire() and accept()
     * to manually acquire and accept messages.
     */
    QPID_DRIVER_EXTERN void setAutoAck(size_t n);

    /** Get the set of ID's for messages received by this subscription but not yet acquired.
     * This will always be empty if  acquireMode=ACQUIRE_MODE_PRE_ACQUIRED
     */
    QPID_DRIVER_EXTERN SequenceSet getUnacquired() const;

    /** Get the set of ID's for messages acquired by this subscription but not yet accepted. */
    QPID_DRIVER_EXTERN SequenceSet getUnaccepted() const;

    /** Acquire messageIds and remove them from the un-acquired set for the session. */
    QPID_DRIVER_EXTERN void acquire(const SequenceSet& messageIds);

    /** Accept messageIds and remove them from the un-accepted set for the session. */
    QPID_DRIVER_EXTERN void accept(const SequenceSet& messageIds);

    /** Release messageIds and remove them from the un-accepted set for the session. */
    QPID_DRIVER_EXTERN void release(const SequenceSet& messageIds);

    /** Get the session associated with this subscription */
    QPID_DRIVER_EXTERN Session getSession() const;

    /** Get the subscription manager associated with this subscription */
    QPID_DRIVER_EXTERN SubscriptionManager getSubscriptionManager();

    /** Send subscription request and issue appropriate flow control commands. */
    QPID_DRIVER_EXTERN void subscribe();

    /** Cancel the subscription. */
    QPID_DRIVER_EXTERN void cancel();

    /** Grant specified credit for this subscription **/
    QPID_DRIVER_EXTERN void grantCredit(framing::message::CreditUnit unit, uint32_t value);

    QPID_DRIVER_EXTERN void received(Message&);

    /**
     * Set up demux diversion for messages sent to this subscription
     */
    Demux::QueuePtr divert();
    /**
     * Cancel any demux diversion that may have been setup for this
     * subscription
     */
    QPID_DRIVER_EXTERN void cancelDiversion();

  private:

    mutable sys::Mutex lock;
    SubscriptionManagerImpl& manager;
    std::string name, queue;
    SubscriptionSettings settings;
    framing::SequenceSet unacquired, unaccepted;
    MessageListener* listener;
    std::auto_ptr<ScopedDivert> demuxRule;
};

}} // namespace qpid::driver

#endif  /*!QPID_DRIVER_SUBSCRIPTION_IMPL_H*/