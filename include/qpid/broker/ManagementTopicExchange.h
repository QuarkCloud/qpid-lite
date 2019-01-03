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
#ifndef QPID_BROKER_MANAGEMENT_TOPIC_EXCHANGE_H
#define QPID_BROKER_MANAGEMENT_TOPIC_EXCHANGE_H 1

#include "qpid/broker/TopicExchange.h"
#include "qpid/broker/ManagementAgent.h"

namespace qpid {
namespace broker {

class ManagementTopicExchange : public virtual TopicExchange
{
  private:
    ManagementAgent* managementAgent;
    int qmfVersion;
 
  public:
    static const std::string typeName;

    ManagementTopicExchange(const std::string& name, ::qmf2::Manageable* _parent = 0, Broker* broker = 0);
    ManagementTopicExchange(const std::string& _name, bool _durable,
                            const qpid::framing::FieldTable& _args,
		::qmf2::Manageable* _parent = 0, Broker* broker = 0);

    virtual std::string getType() const { return typeName; }

    virtual void route(Deliverable& msg);

    virtual bool bind(Queue::shared_ptr queue,
                      const std::string& routingKey,
                      const qpid::framing::FieldTable* args);

    void setManagmentAgent(ManagementAgent* agent, int qmfVersion);

    virtual ~ManagementTopicExchange();
};


}
}

#endif /**QPID_BROKER_MANAGEMENT_TOPIC_EXCHANGE_H*/