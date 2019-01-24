#ifndef QPID_SYS_AUTO_PTR_H
#define QPID_SYS_AUTO_PTR_H 1

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

#include <memory>
namespace qpid {
	namespace sys {
		/** Convenient template for creating auto_ptr in-place in an argument list. */
		template <class T>
		std::auto_ptr<T> make_auto_ptr(T* ptr) { return std::auto_ptr<T>(ptr); }
	}
} // namespace qpid::sys



#endif  /*!QPID_SYS_AUTO_PTR_H*/
