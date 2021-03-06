#ifndef QPID_SYS_ATOMIC_VALUE_H
#define QPID_SYS_ATOMIC_VALUE_H 1

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

#if defined( __GNUC__ ) && __GNUC__ >= 4 && ( defined( __i686__ ) || defined( __x86_64__ ) )
// Use the Gnu C built-in atomic operations if compiling with gcc on a suitable platform.
#include "qpid/sys/posix/AtomicValue_gcc.h"

#else
// Fall-back to mutex locked operations if we don't have atomic ops.
#include "qpid/sys/windows/AtomicValue.h"
#endif

#endif  /*!QPID_SYS_ATOMIC_VALUE_H*/
