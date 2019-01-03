#ifndef QMF2_DATA_ADDR_H
#define QMF2_DATA_ADDR_H
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
#include "qpid/types/Variant.h"
#include <string>

namespace qmf2 {

#ifndef SWIG
    template <class> class PrivateImplRef;
#endif

    class DataAddrImpl;

    class QMF2_CLASS_EXTERN DataAddr : public qmf2::Handle<DataAddrImpl> {
    public:
        QMF2_EXTERN DataAddr(DataAddrImpl* impl = 0);
        QMF2_EXTERN DataAddr(const DataAddr&);
        QMF2_EXTERN DataAddr& operator=(const DataAddr&);
        QMF2_EXTERN ~DataAddr();

        QMF2_EXTERN bool operator==(const DataAddr&);
        QMF2_EXTERN bool operator<(const DataAddr&);

        QMF2_EXTERN DataAddr(const qpid::types::Variant::Map&);
        QMF2_EXTERN DataAddr(const std::string& name, const std::string& agentName, uint32_t agentEpoch=0);
        QMF2_EXTERN const std::string& getName() const;
        QMF2_EXTERN const std::string& getAgentName() const;
        QMF2_EXTERN uint32_t getAgentEpoch() const;
        QMF2_EXTERN qpid::types::Variant::Map asMap() const;

        QMF2_EXTERN bool operator==(const DataAddr&) const;
        QMF2_EXTERN bool operator<(const DataAddr&) const;

#ifndef SWIG
    private:
        friend class qmf2::PrivateImplRef<DataAddr>;
        friend struct DataAddrImplAccess;
#endif
    };

}

#endif
