#ifndef _QMF2_SCHEMA_IMPL_H_
#define _QMF2_SCHEMA_IMPL_H_ 1
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
#include "qmf2/PrivateImplRef.h"
#include "qmf2/exceptions.h"
#include "qmf2/SchemaTypes.h"
#include "qmf2/SchemaId.h"
#include "qmf2/Schema.h"
#include "qmf2/SchemaProperty.h"
#include "qmf2/SchemaMethod.h"
#include "qmf2/Buffer.h"
#include <list>

namespace qmf2 {
    class SchemaImpl : public virtual qpid::sys::RefCounted {
    public:
        //
        // Impl-only public methods
        //
        SchemaImpl(const qpid::types::Variant::Map& m);
        qpid::types::Variant::Map asMap() const;
        SchemaImpl(Buffer& v1Buffer);
        std::string asV1Content(uint32_t sequence) const;
        bool isValidProperty(const std::string& k, const qpid::types::Variant& v) const;
        bool isValidMethodInArg(const std::string& m, const std::string& k, const qpid::types::Variant& v) const;
        bool isValidMethodOutArg(const std::string& m, const std::string& k, const qpid::types::Variant& v) const;

        //
        // Methods from API handle
        //
        SchemaImpl(int t, const std::string& p, const std::string& c) : schemaId(t, p, c), finalized(false) {}
        const SchemaId& getSchemaId() const { checkNotFinal(); return schemaId; }

        void finalize();
        bool isFinalized() const { return finalized; }
        void addProperty(const SchemaProperty& p) { checkFinal(); properties.push_back(p); }
        void addMethod(const SchemaMethod& m) { checkFinal(); methods.push_back(m); }

        void setDesc(const std::string& d) { description = d; }
        const std::string& getDesc() const { return description; }

        void setDefaultSeverity(int s) { checkFinal(); defaultSeverity = s; }
        int getDefaultSeverity() const { return defaultSeverity; }

        uint32_t getPropertyCount() const { return properties.size(); }
        SchemaProperty getProperty(uint32_t i) const;

        uint32_t getMethodCount() const { return methods.size(); }
        SchemaMethod getMethod(uint32_t i) const;
    private:
        SchemaId schemaId;
        int defaultSeverity;
        std::string description;
        bool finalized;
        std::list<SchemaProperty> properties;
        std::list<SchemaMethod> methods;

        void checkFinal() const;
        void checkNotFinal() const;
        bool isCompatibleType(int qmfType, qpid::types::VariantType qpidType) const;
    };

    struct SchemaImplAccess
    {
        static SchemaImpl& get(Schema&);
        static const SchemaImpl& get(const Schema&);
    };
}

#endif /**_QMF2_SCHEMA_IMPL_H_*/