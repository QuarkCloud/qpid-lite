#ifndef QPID_BROKER_ACL_ACL_H
#define QPID_BROKER_ACL_ACL_H 1


/*
 *
 * Copyright (c) 2006 The Apache Software Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */



#include "qpid/broker/acl/AclReader.h"
#include "qpid/base/AclHost.h"
#include "qpid/sys/RefCounted.h"
#include "qpid/broker/AclModule.h"
#include "qmf2/Manageable.h"
#include "qpid/broker/ManagementAgent.h"
#include "qpid/broker/manage/Acl.h"
#include "qpid/sys/Mutex.h"

#include <boost/shared_ptr.hpp>
#include <map>
#include <string>


namespace qpid {
	namespace broker {
		class Broker;
		class Connection;


		namespace acl {
			class ConnectionCounter;
			class ResourceCounter;

			struct AclValues {
				std::string aclFile;
				uint16_t    aclMaxConnectPerUser;
				uint16_t    aclMaxConnectPerIp;
				uint16_t    aclMaxConnectTotal;
				uint16_t    aclMaxQueuesPerUser;
			};


			class Acl : public broker::AclModule, public sys::RefCounted, public qmf2::Manageable
			{

			private:
				acl::AclValues                       aclValues;
				broker::Broker*                      broker;
				bool                                 transferAcl;
				boost::shared_ptr<AclData>           data;
				qpid::broker::manage::Acl::shared_ptr mgmtObject;
				::qpid::broker::ManagementAgent*   agent;
				mutable qpid::sys::Mutex             dataLock;
				boost::shared_ptr<ConnectionCounter> connectionCounter;
				boost::shared_ptr<ResourceCounter>   resourceCounter;
				bool                                 userRules;

			public:
				Acl(AclValues& av, broker::Broker& b);

				/** reportConnectLimit
				 * issue management counts and alerts for denied connections
				 */
				void reportConnectLimit(const std::string user, const std::string addr);
				void reportQueueLimit(const std::string user, const std::string queueName);

				inline virtual bool doTransferAcl() {
					return transferAcl;
				};

				inline virtual uint16_t getMaxConnectTotal() {
					return aclValues.aclMaxConnectTotal;
				};

				inline virtual bool userAclRules() {
					return userRules;
				};

				// create specilied authorise methods for cases that need faster matching as needed.
				virtual bool authorise(
					const std::string&               id,
					const Action&                    action,
					const ObjectType&                objType,
					const std::string&               name,
					std::map<Property, std::string>* params = 0);

				virtual bool authorise(
					const std::string&               id,
					const Action&                    action,
					const ObjectType&                objType,
					const std::string&               ExchangeName,
					const std::string&               RoutingKey);

				// Resource quota tracking
				virtual bool approveConnection(const broker::Connection& connection);
				virtual bool approveCreateQueue(const std::string& userId, const std::string& queueName);
				virtual void recordDestroyQueue(const std::string& queueName);

				virtual ~Acl();
			private:
				bool result(
					const AclResult&   aclreslt,
					const std::string& id,
					const Action&      action,
					const ObjectType&  objType,
					const std::string& name);
				bool readAclFile(std::string& errorText);
				bool readAclFile(std::string& aclFile, std::string& errorText);
				void loadEmptyAclRuleset();
				Manageable::status_t lookup(qmf2::Args& args, std::string& text);
				Manageable::status_t lookupPublish(qmf2::Args& args, std::string& text);
				virtual qmf2::ManagementObject::shared_ptr GetManagementObject(void) const;
				virtual qmf2::Manageable::status_t ManagementMethod(uint32_t methodId, qmf2::Args& args, std::string& text);

			};
		}
	}
}// namespace qpid::broker::acl

#endif // QPID_BROKER_ACL_ACL_H
