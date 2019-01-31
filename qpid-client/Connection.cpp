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
#include "qpid/client/Connection.h"
#include "qpid/client/ConnectionImpl.h"
#include "qpid/client/Message.h"
#include "qpid/client/SessionImpl.h"
#include "qpid/client/SessionBase0_10Access.h"
#include "qpid/sys/Url.h"
#include "qpid/sys/Logger.h"
#include "qpid/sys/Statement.h"
#include "qpid/framing/AMQP_HighestVersion.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <functional>
#include <boost/format.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

using namespace qpid::framing;
using namespace qpid::sys;


namespace qpid {
namespace client {

Connection::Connection() : version(framing::ProtocolVersion(0, 10))
{
    ConnectionImpl::init();
}

Connection::~Connection() {}

void Connection::open(
    const sys::Url& url,
    const std::string& uid, const std::string& pwd, 
    const std::string& vhost,
    uint16_t maxFrameSize)
{
	amqp::ConnectionOptions settings;
    settings.username = uid;
    settings.password = pwd;
    settings.virtualhost = vhost;
    settings.maxFrameSize = maxFrameSize;
    open(url, settings);
}

void Connection::open(const sys::Url& url, const amqp::ConnectionOptions& settings) {
    if (url.empty())
        throw sys::Exception(QPID_MSG("Attempt to open URL with no addresses."));
    sys::Url::const_iterator i = url.begin();
    do {
        const Address& addr = *i;
        i++;
        try {
			amqp::ConnectionOptions cs(settings);
            if (addr.protocol.size()) cs.protocol = addr.protocol;
            cs.host = addr.host;
            cs.port = addr.port;
            open(cs);
            break;
        }
        catch (const Exception& /*e*/) {
            if (i == url.end()) throw;
        }
    } while (i != url.end());
}

void Connection::open(
    const std::string& host, int port,
    const std::string& uid, const std::string& pwd, 
    const std::string& vhost,
    uint16_t maxFrameSize)
{
	amqp::ConnectionOptions settings;
    settings.host = host;
    settings.port = port;
    settings.username = uid;
    settings.password = pwd;
    settings.virtualhost = vhost;
    settings.maxFrameSize = maxFrameSize;
    open(settings);
}

bool Connection::isOpen() const {
    return impl && impl->isOpen();
}

void 
Connection::registerFailureCallback ( boost::function<void ()> fn ) {
    failureCallback = fn;
    if ( impl )
        impl->registerFailureCallback ( fn );
}



void Connection::open(const amqp::ConnectionOptions& settings)
{
    if (isOpen())
        throw Exception(QPID_MSG("Connection::open() was already called"));

    impl = ConnectionImpl::create(version, settings);
    impl->open();
    if ( failureCallback )
        impl->registerFailureCallback ( failureCallback );
}

const amqp::ConnectionOptions& Connection::getNegotiatedSettings() const
{
    if (!isOpen())
        throw Exception(QPID_MSG("Connection is not open."));
     return impl->getNegotiatedSettings();
}

Session Connection::newSession(const std::string& name, uint32_t timeout) {
    if (!isOpen())
        throw TransportFailure("Can't create session, connection is not open");
    Session s;
    SessionBase0_10Access(s).set(impl->newSession(name, timeout));
    return s;
}

void Connection::resume(Session& session) {
    if (!isOpen())
        throw Exception(QPID_MSG("Connection is not open."));
    impl->addSession(session.impl);
    session.impl->resume(impl);
}

void Connection::close() {
    if ( impl )
        impl->close();
}

std::vector<sys::Url> Connection::getInitialBrokers() {
    return impl ? impl->getInitialBrokers() : std::vector<sys::Url>();
}

}} // namespace qpid::client
