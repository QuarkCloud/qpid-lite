#ifndef __QMF_POSIX_EVENT_NOTIFIER_H
#define __QMF_POSIX_EVENT_NOTIFIER_H

/*
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
 */

#if !defined(QMF_USE_DEPRECATED_API) && !defined(qmf2_EXPORTS) && !defined(SWIG)
#  error "The API defined in this file has been DEPRECATED and will be removed in the future."
#  error "Define 'QMF_USE_DEPRECATED_API' to enable continued use of the API."
#endif

#include <qmf2/Compile.h>
#include "qmf2/Handle.h"
#include "qmf2/AgentSession.h"
#include "qmf2/ConsoleSession.h"

namespace qmf2 {

    class PosixEventNotifierImpl;
    struct PosixEventNotifierImplAccess;

namespace posix {

#ifndef SWIG
  template <class> class PrivateImplRef;
#endif

  class QMF_CLASS_EXTERN EventNotifier : public qmf2::Handle<qmf2::PosixEventNotifierImpl> {
  public:
      QMF_EXTERN EventNotifier(PosixEventNotifierImpl* impl = 0);
      QMF_EXTERN EventNotifier(::qmf2::AgentSession& agentSession);
      QMF_EXTERN EventNotifier(::qmf2::ConsoleSession& consoleSession);
      QMF_EXTERN EventNotifier(const EventNotifier& that);

      QMF_EXTERN ~EventNotifier();

      QMF_EXTERN EventNotifier& operator=(const EventNotifier& that);

      QMF_EXTERN int getHandle() const;

#ifndef SWIG
  private:
      friend class qmf2::PrivateImplRef<EventNotifier>;
      friend struct qmf2::PosixEventNotifierImplAccess;
#endif

  };

}}

#endif

