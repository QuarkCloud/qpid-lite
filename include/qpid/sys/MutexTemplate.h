#ifndef QPID_SYS_MUTEX_TEMPLATE_H
#define QPID_SYS_MUTEX_TEMPLATE_H 1

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

namespace qpid {
namespace sys {

/**
 * Scoped lock template: calls lock() in ctor, unlock() in dtor.
 * L can be any class with lock() and unlock() functions.
 */
template <class L>
class ScopedLock
{
  public:
    ScopedLock(L& l) : mutex(l) { mutex.lock(); }
    ~ScopedLock() { mutex.unlock(); }
  private:
    L& mutex;
};

template <class L>
class ScopedUnlock
{
  public:
    ScopedUnlock(L& l) : mutex(l) { mutex.unlock(); }
    ~ScopedUnlock() { mutex.lock(); }
  private:
    L& mutex;
};

template <class L>
class ScopedRlock
{
  public:
    ScopedRlock(L& l) : mutex(l) { mutex.rlock(); }
    ~ScopedRlock() { mutex.unlock(); }
  private:
    L& mutex;
};

template <class L>
class ScopedWlock
{
  public:
    ScopedWlock(L& l) : mutex(l) { mutex.wlock(); }
    ~ScopedWlock() { mutex.unlock(); }
  private:
    L& mutex;
};

template <class L>
class ConditionalScopedLock
{
  public:
    ConditionalScopedLock(L& l) : mutex(l) { acquired = mutex.trylock(); }
    ~ConditionalScopedLock() { if (acquired) mutex.unlock(); }
    bool lockAcquired() { return acquired; }
  private:
    L& mutex;
    bool acquired;
};

}}

#endif  /*!QPID_SYS_MUTEX_TEMPLATE_H*/
