
#ifndef QPID_DRIVER_CONNECTION_HANDLER_H
#define QPID_DRIVER_CONNECTION_HANDLER_H 1
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

#include "qpid/driver/ChainableFrameHandler.h"
#include "qpid/driver/StateManager.h"
#include "qpid/driver/Bounds.h"

#include "qpid/amqp/ConnectionOptions.h"

#include "qpid/framing/AMQMethodBody.h"
#include "qpid/framing/AMQP_HighestVersion.h"
#include "qpid/framing/AMQP_ClientOperations.h"
#include "qpid/framing/AMQP_ServerProxy.h"
#include "qpid/framing/Array.h"
#include "qpid/framing/enum.h"
#include "qpid/framing/FieldTable.h"
#include "qpid/framing/FrameHandler.h"
#include "qpid/framing/InputHandler.h"
#include "qpid/sys/SecurityLayer.h"
#include "qpid/sys/SecuritySettings.h"
#include "qpid/sys/Timer.h"
#include "qpid/sys/Url.h"
#include "qpid/sys/Sasl.h"
#include <memory>

namespace qpid {
namespace driver {

class ConnectionHandler : private StateManager,
	public amqp::ConnectionOptions,
                          public ChainableFrameHandler,
                          public framing::InputHandler,
                          private framing::AMQP_ClientOperations::ConnectionHandler
{
    typedef framing::AMQP_ClientOperations::ConnectionHandler ConnectionOperations;
    enum STATES {NOT_STARTED, NEGOTIATING, OPENING, OPEN, CLOSING, CLOSED, FAILED};
    std::set<int> ESTABLISHED, FINISHED;

    class Adapter : public framing::FrameHandler
    {
        ConnectionHandler& handler;
        Bounds& bounds;
    public:
        Adapter(ConnectionHandler& h, Bounds& bounds);
        void handle(framing::AMQFrame& f);
    }; 

    Adapter outHandler;
    framing::AMQP_ServerProxy::Connection proxy;
    framing::connection::CloseCode errorCode;
    std::string errorText;
    bool insist;
    framing::ProtocolVersion version;
    framing::Array capabilities;
    framing::FieldTable properties;
    std::auto_ptr<qpid::sys::Sasl> sasl;
    std::auto_ptr<qpid::sys::SecurityLayer> securityLayer;
    boost::intrusive_ptr<qpid::sys::TimerTask> rcvTimeoutTask;
    std::string operUserId;

    void checkState(STATES s, const std::string& msg);

    //methods corresponding to connection controls:
    void start(const framing::FieldTable& serverProperties,
               const framing::Array& mechanisms,
               const framing::Array& locales);    
    void secure(const std::string& challenge);    
    void tune(uint16_t channelMax,
              uint16_t frameMax,
              uint16_t heartbeatMin,
              uint16_t heartbeatMax);    
    void openOk(const framing::Array& knownHosts);    
    void redirect(const std::string& host,
                  const framing::Array& knownHosts);    
    void close(uint16_t replyCode, const std::string& replyText);    
    void closeOk();
    void heartbeat();

public:
    using InputHandler::handle;
    typedef boost::function<void()> CloseListener;    
    typedef boost::function<void(uint16_t, const std::string&)> ErrorListener;
    typedef boost::function<const qpid::sys::SecuritySettings*()> GetSecuritySettings;

    ConnectionHandler(const amqp::ConnectionOptions&, framing::ProtocolVersion&, Bounds&);

    void received(framing::AMQFrame& f) { incoming(f); } 

    void incoming(framing::AMQFrame& frame);
    void outgoing(framing::AMQFrame& frame);

    void waitForOpen();
    void close();
    void fail(const std::string& message);

    // Note that open and closed aren't related by open = !closed
    bool isOpen() const;
    bool isClosed() const;
    bool isClosing() const;

    std::auto_ptr<qpid::sys::SecurityLayer> getSecurityLayer();
    void setRcvTimeoutTask(boost::intrusive_ptr<qpid::sys::TimerTask>);

    CloseListener onClose;
    ErrorListener onError;

    std::vector<qpid::sys::Url> knownBrokersUrls;

    static framing::connection::CloseCode convert(uint16_t replyCode);
    const std::string& getUserId() const { return operUserId; }
    GetSecuritySettings  getSecuritySettings;     /** query the transport for its security details */
};

}}

#endif /**QPID_DRIVER_CONNECTION_HANDLER_H*/
