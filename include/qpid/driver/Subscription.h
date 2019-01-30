#ifndef QPID_DRIVER_SUBSCRIPTION_H
#define QPID_DRIVER_SUBSCRIPTION_H 1

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

#include "qpid/driver/Handle.h"
#include "qpid/driver/Session.h"
#include "qpid/driver/SubscriptionSettings.h"
#include "qpid/driver/Message.h"
#include "qpid/driver/Compile.h"

namespace qpid {
namespace driver {

template <class> class PrivateImplRef;
class SubscriptionImpl;
class SubscriptionManager;

/**
 * A handle to an active subscription. Provides methods to query the subscription status
 * and control acknowledgement (acquire and accept) of messages.
 */
class QPID_DRIVER_CLASS_EXTERN Subscription : public Handle<SubscriptionImpl> {
  public:
    QPID_DRIVER_EXTERN Subscription(SubscriptionImpl* = 0);
    QPID_DRIVER_EXTERN Subscription(const Subscription&);
    QPID_DRIVER_EXTERN ~Subscription();
    QPID_DRIVER_EXTERN Subscription& operator=(const Subscription&);


    /** The name of the subscription, used as the "destination" for messages from the broker.
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
    QPID_DRIVER_EXTERN void setAutoAck(unsigned int n);

    /** Get the set of ID's for messages received by this subscription but not yet acquired.
     * This will always be empty if getSettings().acquireMode=ACQUIRE_MODE_PRE_ACQUIRED
     */
    QPID_DRIVER_EXTERN SequenceSet getUnacquired() const;

    /** Get the set of ID's for messages received by this subscription but not yet accepted. */
    QPID_DRIVER_EXTERN SequenceSet getUnaccepted() const;

    /** Acquire messageIds and remove them from the unacquired set.
     * oAdd them to the unaccepted set if getSettings().acceptMode == ACCEPT_MODE_EXPLICIT.
     */
    QPID_DRIVER_EXTERN void acquire(const SequenceSet& messageIds);

    /** Accept messageIds and remove them from the unaccepted set.
     *@pre messageIds is a subset of getUnaccepted()
     */
    QPID_DRIVER_EXTERN void accept(const SequenceSet& messageIds);

    /** Release messageIds and remove them from the unaccepted set.
     *@pre messageIds is a subset of getUnaccepted()
     */
    QPID_DRIVER_EXTERN void release(const SequenceSet& messageIds);

    /* Acquire a single message */
    QPID_DRIVER_INLINE_EXTERN void acquire(const Message& m) { acquire(SequenceSet(m.getId())); }

    /* Accept a single message */
	QPID_DRIVER_INLINE_EXTERN void accept(const Message& m) { accept(SequenceSet(m.getId())); }

    /* Release a single message */
	QPID_DRIVER_INLINE_EXTERN void release(const Message& m) { release(SequenceSet(m.getId())); }

    /** Get the session associated with this subscription */
    QPID_DRIVER_EXTERN Session getSession() const;

    /** Get the subscription manager associated with this subscription */
    QPID_DRIVER_EXTERN SubscriptionManager getSubscriptionManager();

    /** Cancel the subscription. */
    QPID_DRIVER_EXTERN void cancel();

    /** Grant the specified amount of message credit */
    QPID_DRIVER_EXTERN void grantMessageCredit(uint32_t);

    /** Grant the specified amount of byte credit */
    QPID_DRIVER_EXTERN void grantByteCredit(uint32_t);

  private:
  friend class PrivateImplRef<Subscription>;
  friend class SubscriptionManager;
};
}} // namespace qpid::driver

#endif  /*!QPID_DRIVER_SUBSCRIPTION_H*/
