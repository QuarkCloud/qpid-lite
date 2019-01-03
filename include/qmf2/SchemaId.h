#ifndef QMF2_SCHEMA_ID_H
#define QMF2_SCHEMA_ID_H
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
#include "qmf2/Handle.h"
#include "qpid/types/Uuid.h"
#include "qmf2/SchemaTypes.h"
#include <string>

namespace qmf2 {

#ifndef SWIG
    template <class> class PrivateImplRef;
#endif

    class SchemaIdImpl;

    class QMF2_CLASS_EXTERN SchemaId : public qmf2::Handle<SchemaIdImpl> {
    public:
        QMF2_EXTERN SchemaId(SchemaIdImpl* impl = 0);
        QMF2_EXTERN SchemaId(const SchemaId&);
        QMF2_EXTERN SchemaId& operator=(const SchemaId&);
        QMF2_EXTERN ~SchemaId();

        QMF2_EXTERN SchemaId(int, const std::string&, const std::string&);
        QMF2_EXTERN void setHash(const qpid::types::Uuid&);
        QMF2_EXTERN int getType() const;
        QMF2_EXTERN const std::string& getPackageName() const;
        QMF2_EXTERN const std::string& getName() const;
        QMF2_EXTERN const qpid::types::Uuid& getHash() const;

#ifndef SWIG
    private:
        friend class qmf2::PrivateImplRef<SchemaId>;
        friend struct SchemaIdImplAccess;
#endif
    };

}

#endif
