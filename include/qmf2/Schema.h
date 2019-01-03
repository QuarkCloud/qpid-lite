#ifndef QMF2_SCHEMA_H
#define QMF2_SCHEMA_H
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

#if !defined(QMF2_USE_DEPRECATED_API) && !defined(qmf2_EXPORTS) && !defined(SWIG)
#  error "The API defined in this file has been DEPRECATED and will be removed in the future."
#  error "Define 'QMF2_USE_DEPRECATED_API' to enable continued use of the API."
#endif

#include <qmf2/Compile.h>
#include "qpid/sys/IntegerTypes.h"
#include "qmf2/Handle.h"
#include "qmf2/SchemaTypes.h"
#include <string>

namespace qmf2 {

#ifndef SWIG
    template <class> class PrivateImplRef;
#endif

    class SchemaImpl;
    class SchemaId;
    class SchemaProperty;
    class SchemaMethod;

    class QMF2_CLASS_EXTERN Schema : public qmf2::Handle<SchemaImpl> {
    public:
        QMF2_EXTERN Schema(SchemaImpl* impl = 0);
        QMF2_EXTERN Schema(const Schema&);
        QMF2_EXTERN Schema& operator=(const Schema&);
        QMF2_EXTERN ~Schema();

        QMF2_EXTERN Schema(int, const std::string&, const std::string&);
        QMF2_EXTERN const SchemaId& getSchemaId() const;

        QMF2_EXTERN void finalize();
        QMF2_EXTERN bool isFinalized() const;
        QMF2_EXTERN void addProperty(const SchemaProperty&);
        QMF2_EXTERN void addMethod(const SchemaMethod&);
        QMF2_EXTERN void setDesc(const std::string&);
        QMF2_EXTERN const std::string& getDesc() const;

        QMF2_EXTERN void setDefaultSeverity(int);
        QMF2_EXTERN int getDefaultSeverity() const;

        QMF2_EXTERN uint32_t getPropertyCount() const;
        QMF2_EXTERN SchemaProperty getProperty(uint32_t) const;

        QMF2_EXTERN uint32_t getMethodCount() const;
        QMF2_EXTERN SchemaMethod getMethod(uint32_t) const;

#ifndef SWIG
    private:
        friend class qmf2::PrivateImplRef<Schema>;
        friend struct SchemaImplAccess;
#endif
    };

}

#endif
