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
#include "qpid/sys/Time.h"
#include <limits>

namespace qpid {
namespace sys {

	MilliDuration::MilliDuration(uint64_t ms) : milliseconds(ms) {}
uint64_t MilliDuration::getMilliseconds() const { return milliseconds; }

MilliDuration operator*(const MilliDuration& duration, uint64_t multiplier)
{
    return MilliDuration(duration.getMilliseconds() * multiplier);
}

MilliDuration operator*(uint64_t multiplier, const MilliDuration& duration)
{
    return MilliDuration(duration.getMilliseconds() * multiplier);
}

bool operator==(const MilliDuration& a, const MilliDuration& b)
{
    return a.getMilliseconds() == b.getMilliseconds();
}

bool operator!=(const MilliDuration& a, const MilliDuration& b)
{
    return a.getMilliseconds() != b.getMilliseconds();
}

const MilliDuration MilliDuration::FOREVER(std::numeric_limits<uint64_t>::max());
const MilliDuration MilliDuration::IMMEDIATE(0);
const MilliDuration MilliDuration::SECOND(1000);
const MilliDuration MilliDuration::MINUTE(SECOND * 60);

}} // namespace qpid::sys
