#ifndef QPID_SYS_SOCKET_ADDRESS_H 
#define QPID_SYS_SOCKET_ADDRESS_H 1

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

#include "qpid/sys/IntegerTypes.h"
#include "qpid/sys/Compile.h"
#include <string>

struct addrinfo;
struct sockaddr;

namespace qpid {
namespace sys {

class SocketAddress {
    friend const ::addrinfo& getAddrInfo(const SocketAddress&);

public:
    /** Create a SocketAddress from hostname and port*/
    QPID_SYS_EXTERN SocketAddress(const std::string& host, const std::string& port);
	QPID_SYS_EXTERN SocketAddress(const SocketAddress&);
	QPID_SYS_EXTERN SocketAddress& operator=(const SocketAddress&);
	QPID_SYS_EXTERN ~SocketAddress();

	QPID_SYS_EXTERN void firstAddress() const;
	QPID_SYS_EXTERN bool nextAddress() const;
	QPID_SYS_EXTERN std::string asString(bool numeric=true,
                                            bool dispNameOnly=false,
                                            bool hideDecoration=false) const;
	QPID_SYS_EXTERN std::string getHost() const;

	QPID_SYS_EXTERN static std::string asString(::sockaddr const * const addr,
                                                   size_t addrlen,
                                                   bool dispNameOnly=false,
                                                   bool hideDecoration=false);
	QPID_SYS_EXTERN static uint16_t getPort(::sockaddr const * const addr);

	QPID_SYS_EXTERN bool isIp() const;

	QPID_SYS_EXTERN std::string comparisonDetails(const SocketAddress& ) const;

	QPID_SYS_EXTERN bool isComparable(const SocketAddress& saHi) const;

	QPID_SYS_EXTERN bool inRange(const SocketAddress& ,
                                    const SocketAddress& ) const;
	QPID_SYS_EXTERN bool inRange(const struct addrinfo&,
                                    const struct addrinfo&,
                                    const struct addrinfo&) const;

	QPID_SYS_EXTERN bool compareAddresses(const struct addrinfo&,
                                             const struct addrinfo&,
                                             int&) const;

private:
    std::string host;
    std::string port;
    mutable ::addrinfo* addrInfo;
    mutable ::addrinfo* currentAddrInfo;
};

}}
#endif  /*!QPID_SYS_SOCKET_ADDRESS_H*/
