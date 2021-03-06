#ifndef QPID_SYS_MODULES_H
#define QPID_SYS_MODULES_H 1

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

#include "qpid/sys/Options.h"
#include <string>
#include <vector>
#include "qpid/sys/Compile.h"

namespace qpid {
	namespace sys {
		struct ModuleOptions : public qpid::sys::Options {
			std::string              loadDir;
			std::vector<std::string> load;
			bool                     noLoad;
			QPID_SYS_EXTERN ModuleOptions(const std::string& defaultModuleDir);
		};

		QPID_SYS_EXTERN void tryShlib(const std::string& libname);
		QPID_SYS_EXTERN void loadModuleDir(std::string dirname, bool isDefault);
	}
} // namespace qpid

#endif  /*!QPID_SYS_MODULES_H*/
