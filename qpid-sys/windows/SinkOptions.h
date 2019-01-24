#ifndef QPID_SYS_WINDOWS_SINKOPTIONS_H
#define QPID_SYS_WINDOWS_SINKOPTIONS_H 1

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

#include "qpid/sys/SinkOptions.h"
#include "qpid/sys/Compile.h"
#include <string>

namespace qpid {
namespace sys {
namespace windows {

struct QPID_SYS_CLASS_EXTERN SinkOptions : public qpid::sys::SinkOptions {
    QPID_SYS_EXTERN SinkOptions(const std::string& argv0);
    virtual ~SinkOptions() {}

	QPID_SYS_EXTERN virtual qpid::sys::SinkOptions& operator=(const qpid::sys::SinkOptions& rhs);

    // This allows the caller to indicate that there's no normal outputs
    // available. For example, when running as a service. In these cases, the
    // platform's "syslog"-type output should replace the default stderr
    // unless some other sink has been selected.
	QPID_SYS_EXTERN virtual void detached(void);

    // The Logger acting on these options calls setup() to request any
    // Sinks be set up and fed back to the logger.
	QPID_SYS_EXTERN virtual void setup(qpid::sys::Logger *logger);

    bool logToStderr;
    bool logToStdout;
    bool logToEventLog;
    std::string eventSource;
    std::string logFile;
};

}}} // namespace qpid::sys::windows

#endif  /*!QPID_SYS_WINDOWS_SINKOPTIONS_H*/
