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

#include "SinkOptions.h"
#include "qpid/sys/SinkOptions.h"
#include "qpid/sys/Logger.h"
#include "qpid/sys/OstreamOutput.h"
#include "qpid/sys/Statement.h"
#include "qpid/sys/memory.h"
#include "qpid/sys/Exception.h"
#include <iostream>
#include <map>
#include <string>

#include <windows.h>

using qpid::sys::Exception;

namespace qpid {
namespace sys {
namespace windows {

namespace {

// 'eventTypes' maps qpid log levels to Windows event types. They are in
// order of qpid log levels and must map to:
// "trace", "debug", "info", "notice", "warning", "error", "critical"
static int eventTypes[qpid::sys::LevelTraits::COUNT] = {
    EVENTLOG_INFORMATION_TYPE,   /* trace */
    EVENTLOG_INFORMATION_TYPE,   /* debug */
    EVENTLOG_INFORMATION_TYPE,   /* info */
    EVENTLOG_INFORMATION_TYPE,   /* notice */
    EVENTLOG_WARNING_TYPE,       /* warning */
    EVENTLOG_ERROR_TYPE,         /* error */
    EVENTLOG_ERROR_TYPE          /* critical */
};

} // namespace

class EventLogOutput : public qpid::sys::Logger::Output {
public:
    EventLogOutput(const std::string& /*sourceName*/) : logHandle(0)
    {
        logHandle = OpenEventLog(0, "Application");
    }

    virtual ~EventLogOutput() {
        if (logHandle)
            CloseEventLog(logHandle);
    }
    
    virtual void log(const Statement& s, const std::string& m)
    {
        if (logHandle) {
          const char *msg = m.c_str();
            ReportEvent(logHandle,
                        eventTypes[s.level],
                        0, /* category unused */
                        0, /* event id */
                        0, /* user security id */
                        1, /* number of strings */
                        0, /* no event-specific data */
                        &msg,
                        0);
        }
    }

private:
    HANDLE logHandle;
};

SinkOptions::SinkOptions(const std::string& /*argv0*/)
    : qpid::sys::SinkOptions(),
      logToStderr(true),
      logToStdout(false),
      logToEventLog(false),
      eventSource("Application")
{
    addOptions()
      ("log-to-stderr", optValue(logToStderr, "yes|no"), "Send logging output to stderr")
      ("log-to-stdout", optValue(logToStdout, "yes|no"), "Send logging output to stdout")
      ("log-to-file", optValue(logFile, "FILE"), "Send log output to FILE.")
      ("log-to-eventlog", optValue(logToEventLog, "yes|no"), "Send logging output to event log;\n\tcustomize using --syslog-name and --syslog-facility")
      ("eventlog-source-name", optValue(eventSource, "Application"), "Event source to log to")
      ;

}

qpid::sys::SinkOptions& SinkOptions::operator=(const qpid::sys::SinkOptions& rhs) {
    const SinkOptions *prhs = dynamic_cast<const SinkOptions*>(&rhs);
    if (this != prhs) {
        logToStderr = prhs->logToStderr;
        logToStdout = prhs->logToStdout;
        logToEventLog = prhs->logToEventLog;
        eventSource = prhs->eventSource;
        logFile = prhs->logFile;
    }
    return *this;
}

void SinkOptions::detached(void) {
    if (logToStderr && !logToStdout && !logToEventLog) {
        logToStderr = false;
        logToEventLog = true;
    }
}

// The Logger acting on these options calls setup() to request any
// Sinks be set up and fed back to the logger.
void SinkOptions::setup(qpid::sys::Logger *logger) {
    if (logToStderr)
        logger->output(qpid::sys::make_auto_ptr<qpid::sys::Logger::Output>
                         (new qpid::sys::OstreamOutput(std::clog)));
    if (logToStdout)
        logger->output(qpid::sys::make_auto_ptr<qpid::sys::Logger::Output>
                         (new qpid::sys::OstreamOutput(std::cout)));

    if (logFile.length() > 0)
        logger->output(qpid::sys::make_auto_ptr<qpid::sys::Logger::Output>
                         (new qpid::sys::OstreamOutput(logFile)));

    if (logToEventLog)
        logger->output(qpid::sys::make_auto_ptr<qpid::sys::Logger::Output>
                         (new EventLogOutput(eventSource)));

}

} // namespace windows

SinkOptions* SinkOptions::create(const std::string& argv0) {
    return new qpid::sys::windows::SinkOptions (argv0);
}

}} // namespace qpid::log::windows
