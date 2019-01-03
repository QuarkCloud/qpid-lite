#ifndef QPID_BROKER_TXBUFFER_H
#define QPID_BROKER_TXBUFFER_H

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

#include "qpid/broker/Compile.h"
#include "qpid/broker/TransactionalStore.h"
#include "qpid/broker/TxOp.h"
#include "qpid/broker/AsyncCompletion.h"
#include "qpid/sys/Mutex.h"
#include <algorithm>
#include <functional>
#include <vector>


namespace qpid {
namespace broker {
class TransactionObserver;

/**
 * Represents a single transaction. As such, an instance of this class
 * will hold a list of operations representing the workload of the
 * transaction. This work can be committed or rolled back. Committing
 * is a two-stage process: first all the operations should be
 * prepared, then if that succeeds they can be committed.
 *
 * In the 2pc case, a successful prepare may be followed by either a
 * commit or a rollback.
 *
 * Atomicity of prepare is ensured by using a lower level
 * transactional facility. This saves explicitly rolling back all the
 * successfully prepared ops when one of them fails. i.e. we do not
 * use 2pc internally, we instead ensure that prepare is atomic at a
 * lower level. This makes individual prepare operations easier to
 * code.
 *
 * Transactions on a messaging broker effect three types of 'action':
 * (1) updates to persistent storage (2) updates to transient storage
 * or cached data (3) network writes.
 *
 * Of these, (1) should always occur atomically during prepare to
 * ensure that if the broker crashes while a transaction is being
 * completed the persistent state (which is all that then remains) is
 * consistent. (3) can only be done on commit, after a successful
 * prepare. There is a little more flexibility with (2) but any
 * changes made during prepare should be subject to the control of the
 * TransactionalStore in use.
 *
 * TxBuffer inherits AsyncCompletion because transactions can be completed
 * asynchronously if the broker is part of a HA cluster.
 */
class TxBuffer : public AsyncCompletion {
  private:
    typedef std::vector<TxOp::shared_ptr>::iterator op_iterator;
    std::vector<TxOp::shared_ptr> ops;
    boost::shared_ptr<TransactionObserver> observer;
    std::auto_ptr<TransactionContext> txContext;
    std::string error;
    sys::Mutex errorLock;

 public:
    QPID_BROKER_EXTERN TxBuffer();

    /**
     * Adds an operation to the transaction.
     */
    QPID_BROKER_EXTERN void enlist(TxOp::shared_ptr op);

    /**
     * Requests that all ops are prepared. This should
     * primarily involve making sure that a persistent record
     * of the operations is stored where necessary.
     *
     * Once prepared, a transaction can be committed (or in
     * the 2pc case, rolled back).
     *
     * @returns true if all the operations prepared
     * successfully, false if not.
     */
    QPID_BROKER_EXTERN bool prepare(TransactionContext* const ctxt);

    /**
     * Signals that the ops all prepared successfully and can
     * now commit, i.e. the operation can now be fully carried
     * out.
     *
     * Should only be called after a call to prepare() returns
     * true.
     */
    QPID_BROKER_EXTERN void commit();

    /**
     * Signals that all ops can be rolled back.
     *
     * Should only be called either after a call to prepare()
     * returns true (2pc) or instead of a prepare call
     * ('server-local')
     */
    QPID_BROKER_EXTERN void rollback();

    /**
     * Start a local commit - may complete asynchronously.
     */
    QPID_BROKER_EXTERN void startCommit(TransactionalStore* const store);

    /** End a commit, called via async completion.
     *@return encoded result, not used here.
     */
    QPID_BROKER_EXTERN std::string endCommit(TransactionalStore* const store);

    QPID_BROKER_EXTERN void setObserver(boost::shared_ptr<TransactionObserver> o) {
        observer = o;
    }

    QPID_BROKER_EXTERN boost::shared_ptr<TransactionObserver> getObserver() const {
        return observer;
    }

    /** Set an error to be raised from endCommit when the commit completes.
     * Called from completer threads if we are doing async completion.
     * This is the only TxBuffer function called outside the IO thread.
     */
    QPID_BROKER_EXTERN void setError(const std::string& message);
};

}} // namespace qpid::broker


#endif  /*!QPID_BROKER_TXBUFFER_H*/
