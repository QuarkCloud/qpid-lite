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
#ifndef QPID_FRAMING_SEQUENCE_SET_H
#define QPID_FRAMING_SEQUENCE_SET_H 1

#include "qpid/framing/SequenceNumber.h"
#include "qpid/framing/RangeSet.h"
#include "qpid/framing/Compile.h"

namespace qpid {
namespace framing {
class Buffer;

class QPID_FRAMING_CLASS_EXTERN SequenceSet : public RangeSet<SequenceNumber> {
  public:
    SequenceSet() {}
    SequenceSet(const RangeSet<SequenceNumber>& r)
        : RangeSet<SequenceNumber>(r) {}
    SequenceSet(const SequenceNumber& s) { add(s); }
    SequenceSet(const SequenceNumber& start, const SequenceNumber finish) { add(start,finish); }


    QPID_FRAMING_EXTERN void encode(Buffer& buffer) const;
    QPID_FRAMING_EXTERN void decode(Buffer& buffer);
    QPID_FRAMING_EXTERN uint32_t encodedSize() const;

    QPID_FRAMING_EXTERN bool contains(const SequenceNumber& s) const;
    QPID_FRAMING_EXTERN void add(const SequenceNumber& s);
    QPID_FRAMING_EXTERN void add(const SequenceNumber& start, const SequenceNumber& finish); // Closed range
    QPID_FRAMING_EXTERN void add(const SequenceSet& set);
    QPID_FRAMING_EXTERN void remove(const SequenceNumber& s);
    QPID_FRAMING_EXTERN void remove(const SequenceNumber& start, const SequenceNumber& finish); // Closed range
    QPID_FRAMING_EXTERN void remove(const SequenceSet& set);

    template <class T> void for_each(T& t) const {
        for (RangeIterator i = rangesBegin(); i != rangesEnd(); i++)
            t(i->first(), i->last());
        }

    template <class T> void for_each(const T& t) const {
        for (RangeIterator i = rangesBegin(); i != rangesEnd(); i++)
            t(i->first(), i->last());
    }

  friend QPID_FRAMING_EXTERN std::ostream& operator<<(std::ostream&, const SequenceSet&);
};

}} // namespace qpid::framing


#endif /**QPID_FRAMING_SEQUENCE_SET_H*/
