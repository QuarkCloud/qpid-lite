#ifndef QPID_FRAMING_PROXY_H
#define QPID_FRAMING_PROXY_H 1

/*
 *
 * Copyright (c) 2006 The Apache Software Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "qpid/framing/FrameHandler.h"
#include "qpid/framing/ProtocolVersion.h"

#include "qpid/framing/Compile.h"

namespace qpid {
namespace framing {

class AMQBody;

/**
 * Base class for proxies.
 */
class Proxy
{
  public:
    class ScopedSync
    {
        Proxy& proxy;
      public:
        QPID_FRAMING_EXTERN ScopedSync(Proxy& p);
        QPID_FRAMING_EXTERN ~ScopedSync();
    };

    QPID_FRAMING_EXTERN Proxy(FrameHandler& h);
    QPID_FRAMING_EXTERN virtual ~Proxy();

    QPID_FRAMING_EXTERN void send(const AMQBody&);

    QPID_FRAMING_EXTERN ProtocolVersion getVersion() const;

    QPID_FRAMING_EXTERN FrameHandler& getHandler();
    QPID_FRAMING_EXTERN void setHandler(FrameHandler&);
  private:
    FrameHandler* out;
    bool sync;
};

}} // namespace qpid::framing



#endif  /*QPID_FRAMING_PROXY_H*/
