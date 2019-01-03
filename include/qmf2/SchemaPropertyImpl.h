#ifndef _QMF2_SCHEMA_PROPERTY_IMPL_H_
#define _QMF2_SCHEMA_PROPERTY_IMPL_H_

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

#include "qpid/sys/RefCounted.h"
#include "qmf2/SchemaTypes.h"
#include "qmf2/SchemaProperty.h"
#include "qpid/types/Variant.h"
#include "qmf2/Buffer.h"

namespace qpid {
namespace management {
    class Buffer;
}}

namespace qmf2 {
    class Hash;
    class SchemaPropertyImpl : public virtual qpid::sys::RefCounted {
    public:
        //
        // Public impl-only methods
        //
        SchemaPropertyImpl(const qpid::types::Variant::Map& m);
        SchemaPropertyImpl(qmf2::Buffer& v1Buffer);
        qpid::types::Variant::Map asMap() const;
        void updateHash(Hash&) const;
        void encodeV1(qmf2::Buffer&, bool isArg, bool isMethodArg) const;

        //
        // Methods from API handle
        //
        SchemaPropertyImpl(const std::string& n, int t, const std::string o);
        void setAccess(int a) { access = a; }
        void setIndex(bool i) { index = i; }
        void setOptional(bool o) { optional = o; }
        void setUnit(const std::string& u) { unit = u; }
        void setDesc(const std::string& d) { desc = d; }
        void setSubtype(const std::string& s) { subtype = s; }
        void setDirection(int d) { direction = d; }

        const std::string& getName() const { return name; }
        int getType() const { return dataType; }
        int getAccess() const { return access; }
        bool isIndex() const { return index; }
        bool isOptional() const { return optional; }
        const std::string& getUnit() const { return unit; }
        const std::string& getDesc() const { return desc; }
        const std::string& getSubtype() const { return subtype; }
        int getDirection() const { return direction; }

    private:
        std::string name;
        int dataType;
        std::string subtype;
        int access;
        bool index;
        bool optional;
        std::string unit;
        std::string desc;
        int direction;

        uint8_t v1TypeCode() const;
        void fromV1TypeCode(int8_t);
    };

    struct SchemaPropertyImplAccess
    {
        static SchemaPropertyImpl& get(SchemaProperty&);
        static const SchemaPropertyImpl& get(const SchemaProperty&);
    };
}

#endif
