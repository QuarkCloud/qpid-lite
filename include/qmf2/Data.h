#ifndef QMF2_DATA_H
#define QMF2_DATA_H
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
#include "qmf2/exceptions.h"
#include "qpid/types/Variant.h"
#include <string>

namespace qmf2 {

#ifndef SWIG
    template <class> class PrivateImplRef;
#endif

    class DataImpl;
    class Schema;
    class SchemaId;
    class DataAddr;
    class Agent;

    class QMF2_CLASS_EXTERN Data : public qmf2::Handle<DataImpl> {
    public:
        QMF2_EXTERN Data(DataImpl* impl = 0);
        QMF2_EXTERN Data(const Data&);
        QMF2_EXTERN Data& operator=(const Data&);
        QMF2_EXTERN ~Data();

        QMF2_EXTERN Data(const Schema&);
        QMF2_EXTERN void setAddr(const DataAddr&);
        QMF2_EXTERN void setProperty(const std::string&, const qpid::types::Variant&);
        QMF2_EXTERN void overwriteProperties(const qpid::types::Variant::Map&);
        QMF2_EXTERN bool hasSchema() const;
        QMF2_EXTERN bool hasAddr() const;
        QMF2_EXTERN const SchemaId& getSchemaId() const;
        QMF2_EXTERN const DataAddr& getAddr() const;
        QMF2_EXTERN const qpid::types::Variant& getProperty(const std::string&) const;
        QMF2_EXTERN const qpid::types::Variant::Map& getProperties() const;
        QMF2_EXTERN bool hasAgent() const;
        QMF2_EXTERN const Agent& getAgent() const;

#ifndef SWIG
    private:
        friend class qmf2::PrivateImplRef<Data>;
        friend struct DataImplAccess;
#endif
    };

}

#endif
