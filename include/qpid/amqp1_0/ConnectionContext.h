#ifndef QPID_AMQP1_0_CONNECTION_CONTEXT_H
#define QPID_AMQP1_0_CONNECTION_CONTEXT_H 1

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
#include <deque>
#include <map>
#include <memory>
#include <string>
#include <boost/intrusive_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "qpid/amqp1_0/SenderContext.h"
#include "qpid/amqp1_0/SessionContext.h"
#include "qpid/amqp1_0/ReceiverContext.h"
#include "qpid/amqp1_0/Sasl.h"

#include "qpid/amqp/ConnectionOptions.h"
#include "qpid/amqp/DriverImpl.h"
#include "qpid/amqp/Message.h"


#include "qpid/sys/Url.h"
#include "qpid/sys/AtomicValue.h"
#include "qpid/sys/ConnectionCodec.h"
#include "qpid/sys/Monitor.h"
#include "qpid/sys/TransportContext.h"
#include "qpid/sys/SecurityLayer.h"
#include "qpid/sys/SecuritySettings.h"
#include "qpid/sys/Timer.h"

#include "qpid/types/Variant.h"


struct pn_connection_t;
struct pn_link_t;
struct pn_session_t;
struct pn_transport_t;


namespace qpid {
	namespace amqp1_0 {

		class ConnectionContext : public qpid::sys::ConnectionCodec, public qpid::amqp::ConnectionOptions, 
			public qpid::sys::TransportContext
		{
		public:
			ConnectionContext(const std::string& url, const qpid::types::Variant::Map& options);
			~ConnectionContext();
			void open();
			bool isOpen() const;
			void close();
			boost::shared_ptr<SessionContext> newSession(bool transactional, const std::string& name);
			boost::shared_ptr<SessionContext> getSession(const std::string& name) const;
			void endSession(boost::shared_ptr<SessionContext>);
			boost::shared_ptr<SenderContext> createSender(boost::shared_ptr<SessionContext>, 
				const qpid::amqp::Address& address);
			boost::shared_ptr<ReceiverContext> createReceiver(boost::shared_ptr<SessionContext>, 
				const qpid::amqp::Address& address);
			boost::shared_ptr<SenderContext> getSender(boost::shared_ptr<SessionContext>, const std::string& name) const;
			boost::shared_ptr<ReceiverContext> getReceiver(boost::shared_ptr<SessionContext>, const std::string& name) const;

			void detach(boost::shared_ptr<SessionContext>, boost::shared_ptr<SenderContext>);
			void detach(boost::shared_ptr<SessionContext>, boost::shared_ptr<ReceiverContext>);
			void drain_and_release_messages(boost::shared_ptr<SessionContext>, boost::shared_ptr<ReceiverContext>);
			bool isClosed(boost::shared_ptr<SessionContext>, boost::shared_ptr<ReceiverContext>);

			// Link operations
			void send(boost::shared_ptr<SessionContext>, boost::shared_ptr<SenderContext> ctxt,
				const qpid::amqp::Message& message, bool sync,
				SenderContext::Delivery** delivery);

			bool fetch(boost::shared_ptr<SessionContext> ssn, boost::shared_ptr<ReceiverContext> lnk, 
				qpid::amqp::Message& message, qpid::sys::MilliDuration timeout);
			bool get(boost::shared_ptr<SessionContext> ssn, boost::shared_ptr<ReceiverContext> lnk, 
				qpid::amqp::Message& message, qpid::sys::MilliDuration timeout);

			// Session operations
			void acknowledge(boost::shared_ptr<SessionContext> ssn, qpid::amqp::Message* message, bool cumulative);
			void commit(boost::shared_ptr<SessionContext> ssn);
			void rollback(boost::shared_ptr<SessionContext> ssn);

			void nack(boost::shared_ptr<SessionContext> ssn, qpid::amqp::Message& message, bool reject);
			void sync(boost::shared_ptr<SessionContext> ssn);
			boost::shared_ptr<ReceiverContext> nextReceiver(boost::shared_ptr<SessionContext> ssn, 
				qpid::sys::MilliDuration timeout);

			void setOption(const std::string& name, const qpid::types::Variant& value);
			std::string getAuthenticatedUsername();

			// Link operations
			void setCapacity(boost::shared_ptr<SenderContext>, uint32_t);
			uint32_t getCapacity(boost::shared_ptr<SenderContext>);
			uint32_t getUnsettled(boost::shared_ptr<SenderContext>);
			void setCapacity(boost::shared_ptr<ReceiverContext>, uint32_t);
			uint32_t getCapacity(boost::shared_ptr<ReceiverContext>);
			uint32_t getAvailable(boost::shared_ptr<ReceiverContext>);
			uint32_t getUnsettled(boost::shared_ptr<ReceiverContext>);


			void activateOutput();
			qpid::sys::Codec& getCodec();
			const qpid::amqp::ConnectionOptions* getOptions();
			const qpid::sys::ConnectionSettings* getSettings() { return getOptions(); }
			//ConnectionCodec interface:
			std::size_t decode(const char* buffer, std::size_t size);
			std::size_t encode(char* buffer, std::size_t size);
			bool canEncode();
			void closed();
			bool isClosed() const;
			sys::ProtocolVersion getVersion() const;
			//additionally, Transport needs:
			void opened();//signal successful connection
			void reconnect(const std::string& url);
			void reconnect();
			std::string getUrl() const;
			const qpid::sys::SecuritySettings* getTransportSecuritySettings();
			void initSecurityLayer(qpid::sys::SecurityLayer&);
			void trace(const char*) const;

		private:
			typedef std::map<std::string, boost::shared_ptr<SessionContext> > SessionMap;
			class CodecAdapter : public qpid::sys::Codec
			{
			public:
				CodecAdapter(ConnectionContext&);
				std::size_t decode(const char* buffer, std::size_t size);
				std::size_t encode(char* buffer, std::size_t size);
				bool canEncode();
			private:
				ConnectionContext& context;
			};

			sys::Url fullUrl;                // Combined URL of all known addresses.
			sys::Url currentUrl;             // URL of currently connected address.

			boost::shared_ptr<amqp::DriverImpl> driver;
			boost::shared_ptr<sys::Transport> transport;

			pn_transport_t* engine;
			pn_connection_t* connection;
			SessionMap sessions;
			mutable qpid::sys::Monitor lock;
			bool writeHeader;
			bool readHeader;
			bool haveOutput;
			std::string id;
			enum {
				DISCONNECTED,
				CONNECTING,
				CONNECTED
			} state;
			std::auto_ptr<Sasl> sasl;
			CodecAdapter codecAdapter;
			bool notifyOnWrite;
			boost::intrusive_ptr<qpid::sys::TimerTask> ticker;

			bool check();
			bool checkDisconnected();
			void waitNoReconnect();

			// NOTE: All wait*() functions must be called in a loop that checks for the
			// waited condition with the lock held.
			void wait();
			void waitUntil(qpid::sys::AbsTime until);
			void wait(boost::shared_ptr<SessionContext>);
			void waitUntil(boost::shared_ptr<SessionContext>, qpid::sys::AbsTime until);
			void wait(boost::shared_ptr<SessionContext>, boost::shared_ptr<ReceiverContext>);
			void wait(boost::shared_ptr<SessionContext>, boost::shared_ptr<SenderContext>);
			void waitUntil(boost::shared_ptr<SessionContext>, boost::shared_ptr<ReceiverContext>, qpid::sys::AbsTime until);
			void waitUntil(boost::shared_ptr<SessionContext>, boost::shared_ptr<SenderContext>, qpid::sys::AbsTime until);

			void checkClosed(boost::shared_ptr<SessionContext>);
			void checkClosed(boost::shared_ptr<SessionContext>, boost::shared_ptr<ReceiverContext>);
			void checkClosed(boost::shared_ptr<SessionContext>, boost::shared_ptr<SenderContext>);
			void checkClosed(boost::shared_ptr<SessionContext>, pn_link_t*);

			void wakeupDriver();
			void attach(boost::shared_ptr<SessionContext>, pn_link_t*, int credit = 0);
			void attach(boost::shared_ptr<SessionContext>, boost::shared_ptr<SenderContext>);
			void attach(boost::shared_ptr<SessionContext>, boost::shared_ptr<ReceiverContext>);
			void autoconnect();
			bool tryConnectUrl(const qpid::sys::Url& url);
			bool tryOpenAddr(const qpid::sys::Address& address);
			bool tryConnectAddr(const qpid::sys::Address& address);
			void reconnect(const sys::Url& url);
			void reset();
			bool restartSessions();
			void restartSession(boost::shared_ptr<SessionContext>);

			std::size_t decodePlain(const char* buffer, std::size_t size);
			std::size_t encodePlain(char* buffer, std::size_t size);
			bool canEncodePlain();

			std::size_t readProtocolHeader(const char* buffer, std::size_t size);
			std::size_t writeProtocolHeader(char* buffer, std::size_t size);
			std::string getError();

			void configureConnection();
			bool checkTransportError(std::string&);
			bool useSasl();
			void setProperties();

			void discharge(boost::shared_ptr<SessionContext>, bool fail);
			void startTxSession(boost::shared_ptr<SessionContext>);

			void syncLH(boost::shared_ptr<SessionContext> ssn, sys::Monitor::ScopedLock&);
			void sendLH(boost::shared_ptr<SessionContext>, boost::shared_ptr<SenderContext> ctxt,
				const qpid::amqp::Message& message, bool sync,
				SenderContext::Delivery** delivery, sys::Monitor::ScopedLock&);
			void acknowledgeLH(boost::shared_ptr<SessionContext> ssn, 
				qpid::amqp::Message* message, bool cumulative, sys::Monitor::ScopedLock&);

			types::Variant::List getPeersOfferedCapabilities();
			bool usePassthrough();
			qpid::amqp::Address passthrough(const qpid::amqp::Address&);
		};
	}
}// namespace qpid::amqp1_0

#endif  /*!QPID_AMQP1_0_CONNECTION_CONTEXT_H*/
