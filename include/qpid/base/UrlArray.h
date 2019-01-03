#ifndef QPID_BASE_URL_ARRAY_H
#define QPID_BASE_URL_ARRAY_H 1

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
#include "qpid/base/Compile.h"
#include "qpid/framing/Array.h"
#include "qpid/sys/Url.h"
#include <vector>

namespace qpid {
	namespace base {

		/** @file Functions to encode/decode an array of URLs. */
		QPID_BASE_EXTERN std::vector<sys::Url> urlArrayToVector(const framing::Array& array);
		QPID_BASE_EXTERN framing::Array vectorToUrlArray(const std::vector<sys::Url>& urls);
	}
} // namespace qpid::base

#endif  /* !QPID_BASE_URL_ARRAY_H */
