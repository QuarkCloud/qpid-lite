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
#include "qpid/amqp0_10/Codecs.h"
#include "qpid/amqp0_10/ConnectionImpl.h"
#include "qpid/amqp0_10/SessionImpl.h"
#include "qpid/amqp/exceptions.h"
#include "qpid/amqp/Session.h"
#include "qpid/amqp/PrivateImplRef.h"

#include "qpid/amqp/DriverImpl.h"
#include "qpid/amqp/ProtocolRegistry.h"

#include "qpid/driver/ConnectionImpl.h"

#include "qpid/framing/Uuid.h"

#include "qpid/sys/Statement.h"
#include "qpid/sys/Options.h"
#include "qpid/sys/Url.h"

#include <boost/intrusive_ptr.hpp>
#include "qpid/config.h"
#include <vector>
#include <sstream>
#include <limits>

namespace qpid {
	namespace amqp0_10 {

		using qpid::types::Variant;
		using qpid::types::VAR_LIST;
		using qpid::framing::Uuid;

		namespace {
			struct DefaultConnectionOptions : qpid::sys::Options
			{
				bool disableAutoDecode;

				DefaultConnectionOptions() : qpid::sys::Options("Connection Option Defaults")
				{
					addOptions()
						("disable-auto-decode", sys::optValue(disableAutoDecode, "TRUE|FALSE"), "Whether to decode amqp 0-10 maps and lists automatically by default");

					sys::CommonOptions common("", "", QPIDC_CONF_FILE);
					try {
						common.parse(0, 0, common.clientConfig, true);
						this->parse(0, 0, common.clientConfig, true);
					}
					catch (const std::exception& e) {
						throw qpid::types::Exception(QPID_MSG("Failed to parse default connection options: " << e.what()));
					}
				}
			};

			const DefaultConnectionOptions& getDefaultOptions()
			{
				static DefaultConnectionOptions defaultOptions;
				return defaultOptions;
			}



			const std::string TCP("tcp");
			const std::string COLON(":");
			double FOREVER(std::numeric_limits<double>::max());

			// Time values in seconds can be specified as integer or floating point values.
			double timeValue(const Variant& value) {
				if (types::isIntegerType(value.getType()))
					return double(value.asInt64());
				return value.asDouble();
			}

			void merge(const std::string& value, std::vector<std::string>& list) {
				if (std::find(list.begin(), list.end(), value) == list.end())
					list.push_back(value);
			}

			void merge(const Variant::List& from, std::vector<std::string>& to)
			{
				for (Variant::List::const_iterator i = from.begin(); i != from.end(); ++i)
					merge(i->asString(), to);
			}

			std::string asString(const std::vector<std::string>& v) {
				std::stringstream os;
				os << "[";
				for (std::vector<std::string>::const_iterator i = v.begin(); i != v.end(); ++i) {
					if (i != v.begin()) os << ", ";
					os << *i;
				}
				os << "]";
				return os.str();
			}

			bool expired(const sys::AbsTime& start, double timeout)
			{
				if (timeout == 0) return true;
				if (timeout == FOREVER) return false;
				sys::NanoDuration used(start, sys::now());
				sys::NanoDuration allowed((int64_t)(timeout*sys::TIME_SEC));
				return allowed < used;
			}

		} // namespace

		ConnectionImpl::ConnectionImpl(const std::string& url, const Variant::Map& options) :
			replaceUrls(false), autoReconnect(false), timeout(FOREVER), limit(-1),
			minReconnectInterval(0.001), maxReconnectInterval(2),
			retries(0), reconnectOnLimitExceeded(true), disableAutoDecode(getDefaultOptions().disableAutoDecode)
		{
			setOptions(options);
			urls.insert(urls.begin(), url);
		}

		void ConnectionImpl::setOptions(const Variant::Map& options)
		{
			for (Variant::Map::const_iterator i = options.begin(); i != options.end(); ++i) {
				setOption(i->first, i->second);
			}
		}

		void ConnectionImpl::setOption(const std::string& name, const Variant& value)
		{
			sys::Mutex::ScopedLock l(lock);
			if (name == "reconnect") {
				autoReconnect = value;
			}
			else if (name == "reconnect-timeout" || name == "reconnect_timeout") {
				timeout = timeValue(value);
			}
			else if (name == "reconnect-limit" || name == "reconnect_limit") {
				limit = value;
			}
			else if (name == "reconnect-interval" || name == "reconnect_interval") {
				maxReconnectInterval = minReconnectInterval = timeValue(value);
			}
			else if (name == "reconnect-interval-min" || name == "reconnect_interval_min") {
				minReconnectInterval = timeValue(value);
			}
			else if (name == "reconnect-interval-max" || name == "reconnect_interval_max") {
				maxReconnectInterval = timeValue(value);
			}
			else if (name == "reconnect-urls-replace" || name == "reconnect_urls_replace") {
				replaceUrls = value.asBool();
			}
			else if (name == "reconnect-urls" || name == "reconnect_urls") {
				if (replaceUrls) urls.clear();
				if (value.getType() == VAR_LIST) {
					merge(value.asList(), urls);
				}
				else {
					merge(value.asString(), urls);
				}
			}
			else if (name == "username") {
				settings.username = value.asString();
			}
			else if (name == "password") {
				settings.password = value.asString();
			}
			else if (name == "sasl-mechanism" || name == "sasl_mechanism" ||
				name == "sasl-mechanisms" || name == "sasl_mechanisms") {
				settings.mechanism = value.asString();
			}
			else if (name == "sasl-service" || name == "sasl_service") {
				settings.service = value.asString();
			}
			else if (name == "sasl-min-ssf" || name == "sasl_min_ssf") {
				settings.minSsf = value;
			}
			else if (name == "sasl-max-ssf" || name == "sasl_max_ssf") {
				settings.maxSsf = value;
			}
			else if (name == "heartbeat") {
				settings.heartbeat = value;
			}
			else if (name == "tcp-nodelay" || name == "tcp_nodelay") {
				settings.tcpNoDelay = value;
			}
			else if (name == "locale") {
				settings.locale = value.asString();
			}
			else if (name == "max-channels" || name == "max_channels") {
				settings.maxChannels = value;
			}
			else if (name == "max-frame-size" || name == "max_frame_size") {
				settings.maxFrameSize = value;
			}
			else if (name == "bounds") {
				settings.bounds = value;
			}
			else if (name == "transport") {
				settings.protocol = value.asString();
			}
			else if (name == "ssl-cert-name" || name == "ssl_cert_name") {
				settings.sslCertName = value.asString();
			}
			else if (name == "ssl-ignore-hostname-verification-failure" || name == "ssl_ignore_hostname_verification_failure") {
				settings.sslIgnoreHostnameVerificationFailure = value;
			}
			else if (name == "x-reconnect-on-limit-exceeded" || name == "x_reconnect_on_limit_exceeded") {
				reconnectOnLimitExceeded = value;
			}
			else if (name == "driver-properties" || name == "client_properties") {
				amqp0_10::translate(value.asMap(), settings.clientProperties);
			}
			else if (name == "disable-auto-decode" || name == "disable_auto_decode") {
				disableAutoDecode = value;
			}
			else if (name == "virtualhost") {
				settings.virtualhost = value.asString();
			}
			else {
				throw qpid::amqp::MessagingException(QPID_MSG("Invalid option: " << name << " not recognised"));
			}
		}


		void ConnectionImpl::close()
		{
			while (true) {
				amqp::Session session;
				{
					qpid::sys::Mutex::ScopedLock l(lock);
					if (sessions.empty()) break;
					session = sessions.begin()->second;
				}
				session.close();
			}
			detach();
		}

		void ConnectionImpl::detach()
		{
			qpid::sys::Mutex::ScopedLock l(lock);
			connection.close();
		}

		bool ConnectionImpl::isOpen() const
		{
			qpid::sys::Mutex::ScopedLock l(lock);
			return connection.isOpen();
		}

		boost::intrusive_ptr<SessionImpl> getImplPtr(qpid::amqp::Session& session)
		{
			return boost::dynamic_pointer_cast<SessionImpl>(
				qpid::amqp::PrivateImplRef<qpid::amqp::Session>::get(session)
				);
		}

		void ConnectionImpl::closed(SessionImpl& s)
		{
			qpid::sys::Mutex::ScopedLock l(lock);
			for (Sessions::iterator i = sessions.begin(); i != sessions.end(); ++i) {
				if (getImplPtr(i->second).get() == &s) {
					sessions.erase(i);
					break;
				}
			}
		}

		qpid::amqp::Session ConnectionImpl::getSession(const std::string& name) const
		{
			qpid::sys::Mutex::ScopedLock l(lock);
			Sessions::const_iterator i = sessions.find(name);
			if (i == sessions.end()) {
				throw qpid::amqp::KeyError("No such session: " + name);
			}
			else {
				return i->second;
			}
		}

		qpid::amqp::Session ConnectionImpl::newSession(bool transactional, const std::string& n)
		{
			std::string name = n.empty() ? Uuid(true).str() : n;
			qpid::amqp::Session impl(new SessionImpl(*this, transactional));
			while (true) {
				try {
					getImplPtr(impl)->setSession(connection.newSession(name));
					qpid::sys::Mutex::ScopedLock l(lock);
					sessions[name] = impl;
					break;
				}
				catch (const qpid::sys::TransportFailure&) {
					reopen();
				}
				catch (const qpid::framing::SessionException& e) {
					SessionImpl::rethrow(e);
				}
				catch (const std::exception& e) {
					throw qpid::amqp::MessagingException(e.what());
				}
			}
			return impl;
		}

		void ConnectionImpl::open()
		{
			qpid::sys::AbsTime start = qpid::sys::now();
			qpid::sys::ScopedLock<qpid::sys::Semaphore> l(semaphore);
			try {
				if (!connection.isOpen()) connect(start);
			}
			catch (const types::Exception&) { throw; }
			catch (const qpid::sys::Exception& e) { throw amqp::ConnectionError(e.what()); }
		}

		void ConnectionImpl::reopen()
		{
			if (!autoReconnect) {
				throw qpid::amqp::TransportFailure("Failed to connect (reconnect disabled)");
			}
			open();
		}


		void ConnectionImpl::connect(const qpid::sys::AbsTime& started)
		{
			QPID_LOG(debug, "Starting connection, urls=" << asString(urls));
			for (double i = minReconnectInterval; !tryConnect(); i = std::min(i * 2, maxReconnectInterval)) {
				if (!autoReconnect) {
					throw qpid::amqp::TransportFailure("Failed to connect (reconnect disabled)");
				}
				if (limit >= 0 && retries++ >= limit) {
					throw qpid::amqp::TransportFailure("Failed to connect within reconnect limit");
				}
				if (expired(started, timeout)) {
					throw qpid::amqp::TransportFailure("Failed to connect within reconnect timeout");
				}
				QPID_LOG(debug, "Connection retry in " << i * 1000 * 1000 << " microseconds, urls="
					<< asString(urls));
				qpid::sys::usleep(int64_t(i * 1000 * 1000)); // Sleep in microseconds.
			}
			QPID_LOG(debug, "Connection successful, urls=" << asString(urls));
			retries = 0;
		}

		void ConnectionImpl::mergeUrls(const std::vector<sys::Url>& more, const sys::Mutex::ScopedLock&) {
			for (std::vector<sys::Url>::const_iterator i = more.begin(); i != more.end(); ++i)
				merge(i->str(), urls);
			QPID_LOG(debug, "Added known-hosts, reconnect-urls=" << asString(urls));
		}

		bool ConnectionImpl::tryConnect()
		{
			sys::Mutex::ScopedLock l(lock);
			for (std::vector<std::string>::const_iterator i = urls.begin(); i != urls.end(); ++i) {
				try {
					QPID_LOG(info, "Trying to connect to " << *i << "...");
					sys::Url url(*i, settings.protocol.size() ? settings.protocol : TCP);
					if (url.getUser().size()) settings.username = url.getUser();
					if (url.getPass().size()) settings.password = url.getPass();
					connection.open(url, settings);
					QPID_LOG(info, "Connected to " << *i);
					mergeUrls(connection.getInitialBrokers(), l);
					return resetSessions(l);
				}
				catch (const amqp::ProtocolVersionError&) {
					throw qpid::amqp::ProtocolVersionError("AMQP 0-10 not supported");
				}
				catch (const qpid::sys::TransportFailure& e) {
					QPID_LOG(info, "Failed to connect to " << *i << ": " << e.what());
				}
			}
			return false;
		}

		bool ConnectionImpl::resetSessions(const sys::Mutex::ScopedLock&)
		{
			try {
				qpid::sys::Mutex::ScopedLock l(lock);
				for (Sessions::iterator i = sessions.begin(); i != sessions.end(); ++i) {
					if (!getImplPtr(i->second)->isTransactional()) {
						getImplPtr(i->second)->setSession(connection.newSession(i->first));
					}
				}
				return true;
			}
			catch (const qpid::sys::TransportFailure& e) {
				QPID_LOG(debug, "Connection Failed to re-initialize sessions: " << e.what());
				return false;
			}
			catch (const qpid::framing::ResourceLimitExceededException& e) {
				if (reconnectOnLimitExceeded) {
					QPID_LOG(debug, "Detaching and reconnecting due to: " << e.what());
					detach();
					return false;
				}
				else {
					throw qpid::amqp::TargetCapacityExceeded(e.what());
				}
			}
		}

		bool ConnectionImpl::backoff()
		{
			if (reconnectOnLimitExceeded) {
				detach();
				open();
				return true;
			}
			else {
				return false;
			}
		}

		void ConnectionImpl::reconnect(const std::string& u)
		{
			sys::Mutex::ScopedLock l(lock);
			try {
				QPID_LOG(info, "Trying to connect to " << u << "...");
				sys::Url url(u, settings.protocol.size() ? settings.protocol : TCP);
				if (url.getUser().size()) settings.username = url.getUser();
				if (url.getPass().size()) settings.password = url.getPass();
				connection.open(url, settings);
				QPID_LOG(info, "Connected to " << u);
				mergeUrls(connection.getInitialBrokers(), l);
				if (!resetSessions(l)) throw qpid::amqp::TransportFailure("Could not re-establish sessions");
			}
			catch (const qpid::sys::TransportFailure& e) {
				QPID_LOG(info, "Failed to connect to " << u << ": " << e.what());
				throw qpid::amqp::TransportFailure(e.what());
			}
			catch (const std::exception& e) {
				QPID_LOG(info, "Error while connecting to " << u << ": " << e.what());
				throw qpid::amqp::MessagingException(e.what());
			}
		}

		void ConnectionImpl::reconnect()
		{
			if (!tryConnect()) {
				throw qpid::amqp::TransportFailure("Could not reconnect");
			}
		}
		std::string ConnectionImpl::getUrl() const
		{
			if (isOpen()) {
				std::stringstream u;
				u << connection.getNegotiatedSettings().protocol << COLON << connection.getNegotiatedSettings().host << COLON << connection.getNegotiatedSettings().port;
				return u.str();
			}
			else {
				return std::string();
			}
		}

		std::string ConnectionImpl::getAuthenticatedUsername()
		{
			return connection.getNegotiatedSettings().username;
		}

		bool ConnectionImpl::getAutoDecode() const
		{
			return !disableAutoDecode;
		}
		bool ConnectionImpl::getAutoReconnect() const
		{
			return autoReconnect;
		}

	}
}// namespace qpid::amqp0_10
