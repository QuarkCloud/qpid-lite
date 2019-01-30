#ifndef QPID_DRIVER_RESULTS_H
#define QPID_DRIVER_RESULTS_H 1

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

#include "qpid/framing/SequenceNumber.h"
#include <map>
#include <boost/shared_ptr.hpp>


namespace qpid {
	namespace driver {

		class FutureResult;

		///@internal
		class Results
		{
		public:
			typedef boost::shared_ptr<FutureResult> FutureResultPtr;

			Results();
			~Results();
			void completed(const framing::SequenceSet& set);
			void received(const framing::SequenceNumber& id, const std::string& result);
			FutureResultPtr listenForResult(const framing::SequenceNumber& point);
			void close();

		private:
			typedef std::map<framing::SequenceNumber, FutureResultPtr> Listeners;
			Listeners listeners;
		};

	}
}
#endif  /**QPID_DRIVER_RESULTS_H*/
