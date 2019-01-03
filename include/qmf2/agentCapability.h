#ifndef QMF2_AGENT_CAPABILITY_H
#define QMF2_AGENT_CAPABILITY_H
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

namespace qmf2 {

    /**
     * Legacy (Qpid 0.7 C++ Agent, 0.7 Broker Agent) capabilities
     */
    const uint32_t AGENT_CAPABILITY_LEGACY = 0;

    /**
     * Qpid 0.8 QMFv2 capabilities
     */
    const uint32_t AGENT_CAPABILITY_0_8             = 1;
    const uint32_t AGENT_CAPABILITY_V2_SCHEMA       = 1;
    const uint32_t AGENT_CAPABILITY_AGENT_PREDICATE = 1;
}

#endif