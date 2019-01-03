#ifndef QPID_SYS_ATOMIC_COUNT_H
#define QPID_SYS_ATOMIC_COUNT_H 1

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

#include <boost/detail/atomic_count.hpp>
#include "qpid/sys/ScopedIncrement.h"

namespace qpid {
namespace sys {

/**
 * Atomic counter.
 */
class AtomicCount {
  public:
    typedef ::qpid::sys::ScopedDecrement<AtomicCount> ScopedDecrement;
    typedef ::qpid::sys::ScopedIncrement<AtomicCount> ScopedIncrement;

    AtomicCount(long value = 0) : count(value) {}
    
    void operator++() { ++count ; }
    
    long operator--() { return --count; }
    
    operator long() const { return count; }

  private:
    boost::detail::atomic_count  count;
};


}}


#endif // QPID_SYS_ATOMIC_COUNT_H
