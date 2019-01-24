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

#include "qpid/sys/Logger.h"
#include "qpid/sys/SinkOptions.h"
#include "qpid/sys/memory.h"
#include "qpid/sys/Thread.h"
#include "qpid/sys/Time.h"
#include "qpid/sys/Exception.h"

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <time.h>


namespace qpid {
namespace sys {


LogOptions::LogOptions(const std::string& argv0_, const std::string& name_) :
	qpid::sys::Options(name_),
	argv0(argv0_),
	name(name_),
	time(true),
	level(true),
	thread(false),
	source(false),
	function(false),
	hiresTs(false),
	category(true),
	trace(false),
	sinkOptions(SinkOptions::create(argv0_))
{
	selectors.push_back("notice+");

	addOptions()
		("trace,t", optValue(trace), "Enables all logging")
		("log-enable", optValue(selectors, "RULE"),
		("Enables logging for selected levels and components. "
			"RULE is in the form 'LEVEL[+-][:PATTERN]'\n"
			"LEVEL is one of: \n\t " + getLevels() + "\n"
			"PATTERN is a logging category name, or a namespace-qualified "
			"function name or name fragment. "
			"Logging category names are: \n\t " + getCategories() + "\n"
			"For example:\n"
			"\t'--log-enable warning+'\n"
			"logs all warning, error and critical messages.\n"
			"\t'--log-enable trace+:Broker'\n"
			"logs all category 'Broker' messages.\n"
			"\t'--log-enable debug:framing'\n"
			"logs debug messages from all functions with 'framing' in the namespace or function name.\n"
			"This option can be used multiple times").c_str())
			("log-disable", optValue(deselectors, "RULE"),
		("Disables logging for selected levels and components. "
			"RULE is in the form 'LEVEL[+-][:PATTERN]'\n"
			"LEVEL is one of: \n\t " + getLevels() + "\n"
			"PATTERN is a logging category name, or a namespace-qualified "
			"function name or name fragment. "
			"Logging category names are: \n\t " + getCategories() + "\n"
			"For example:\n"
			"\t'--log-disable warning-'\n"
			"disables logging all warning, notice, info, debug, and trace messages.\n"
			"\t'--log-disable trace:Broker'\n"
			"disables all category 'Broker' trace messages.\n"
			"\t'--log-disable debug-:qmf::'\n"
			"disables logging debug and trace messages from all functions with 'qmf::' in the namespace.\n"
			"This option can be used multiple times").c_str())
			("log-time", optValue(time, "yes|no"), "Include time in log messages")
		("log-level", optValue(level, "yes|no"), "Include severity level in log messages")
		("log-source", optValue(source, "yes|no"), "Include source file:line in log messages")
		("log-thread", optValue(thread, "yes|no"), "Include thread ID in log messages")
		("log-function", optValue(function, "yes|no"), "Include function signature in log messages")
		("log-hires-timestamp", optValue(hiresTs, "yes|no"), "Use hi-resolution timestamps in log messages")
		("log-category", optValue(category, "yes|no"), "Include category in log messages")
		("log-prefix", optValue(prefix, "STRING"), "Prefix to prepend to all log messages")
		;
	add(*sinkOptions);
}

LogOptions::LogOptions(const LogOptions &o) :
	qpid::sys::Options(o.name),
	argv0(o.argv0),
	name(o.name),
	selectors(o.selectors),
	deselectors(o.deselectors),
	time(o.time),
	level(o.level),
	thread(o.thread),
	source(o.source),
	function(o.function),
	hiresTs(o.hiresTs),
	category(o.category),
	trace(o.trace),
	prefix(o.prefix),
	sinkOptions(SinkOptions::create(o.argv0))
{
	*sinkOptions = *o.sinkOptions;
}

LogOptions& LogOptions::operator=(const LogOptions& x) {
	if (this != &x) {
		argv0 = x.argv0;
		name = x.name;
		selectors = x.selectors;
		deselectors = x.deselectors;
		time = x.time;
		level = x.level;
		thread = x.thread;
		source = x.source;
		function = x.function;
		hiresTs = x.hiresTs;
		category = x.category;
		trace = x.trace;
		prefix = x.prefix;
		*sinkOptions = *x.sinkOptions;
	}
	return *this;
}

std::string getLevels()
{
	std::ostringstream levels;
	levels << LevelTraits::name(Level(0));
	for (int i = 1; i < LevelTraits::COUNT; ++i)
		levels << " " << LevelTraits::name(Level(i));
	return levels.str();
}

std::string getCategories()
{
	std::ostringstream categories;
	categories << CategoryTraits::name(Category(0));
	for (int i = 1; i < CategoryTraits::COUNT; ++i)
		categories << " " << CategoryTraits::name(Category(i));
	return categories.str();
}



inline void Logger::enable_unlocked(Statement* s) {
    s->enabled=selector.isEnabled(s->level, s->function, s->category);
}

namespace {
    sys::PODMutex loggerLock;// = QPID_MUTEX_INITIALIZER;
std::auto_ptr<Logger> logger;
}

Logger& Logger::instance() {
    sys::PODMutex::ScopedLock l(loggerLock);
    if (!logger.get()) logger.reset(new Logger);
    return *logger;
}

Logger::Logger() : flags(0) {
    // Disable automatic logging in Exception constructors to avoid
    // re-entrant use of logger singleton if there is an error in
    // option parsing.
    qpid::sys::DisableExceptionLogging del;

    // Initialize myself from env variables so all programs
    // (e.g. tests) can use logging even if they don't parse
    // command line args.
    LogOptions opts;
    opts.parse(0, 0);
    configure(opts);
}

Logger::~Logger() {}

void Logger::select(const Selector& s) {
    Mutex::ScopedLock l(lock);
    selector=s;
    std::for_each(statements.begin(), statements.end(),
                  boost::bind(&Logger::enable_unlocked, this, _1));
}

Logger::Output::Output()  {}
Logger::Output::~Output() {}

void Logger::log(const Statement& s, const std::string& msg) {
    // Format the message outside the lock.
    std::ostringstream os;
    if (!prefix.empty())
        os << prefix << ": ";
    if (flags&TIME) {
        if (flags&HIRES)
            qpid::sys::outputHiresNow(os);
        else
            qpid::sys::outputFormattedNow(os);
    }
    if (flags&CATEGORY)
        os << "[" << CategoryTraits::name(s.category) << "] ";
    if (flags&LEVEL)
        os << LevelTraits::name(s.level) << " ";
    if (flags&THREAD)
        os << "[0x" << std::hex << qpid::sys::Thread::logId() << "] ";
    if (flags&FILE)
        os << s.file << ":";
    if (flags&LINE)
        os << std::dec << s.line << ":";
    if ((flags&FUNCTION) && s.function)
        os << s.function << ":";
    if (flags & (FILE|LINE|FUNCTION))
        os << " ";
    os << msg << std::endl;
    std::string formatted=os.str();
    {
		Mutex::ScopedLock l(lock);
        std::for_each(outputs.begin(), outputs.end(),
                      boost::bind(&Output::log, _1, s, formatted));
    }
}

void Logger::output(std::auto_ptr<Output> out) {
	Mutex::ScopedLock l(lock);
    outputs.push_back(out.release());
}

void Logger::clear() {
    select(Selector());         // locked
    format(0);                  // locked
	Mutex::ScopedLock l(lock);
    outputs.clear();
}

void Logger::format(int formatFlags) {
	Mutex::ScopedLock l(lock);
    flags=formatFlags;
}

static int bitIf(bool test, int bit) {
    return test ? bit : 0;
}

int Logger::format(const LogOptions& opts) {
    int flags=
        bitIf(opts.level, LEVEL) |
        bitIf(opts.time, TIME) |
        bitIf(opts.source, (FILE|LINE)) |
        bitIf(opts.function, FUNCTION) |
        bitIf(opts.thread, THREAD) |
        bitIf(opts.hiresTs, HIRES) |
        bitIf(opts.category, CATEGORY);
    format(flags);
    return flags;
}

void Logger::add(Statement& s) {
	Mutex::ScopedLock l(lock);
    enable_unlocked(&s);
    statements.insert(&s);
}

void Logger::configure(const LogOptions& opts) {
    clear();
    LogOptions o(opts);
    if (o.trace)
        o.selectors.push_back("trace+");
    format(o);
    select(Selector(o));
    options = opts;
    setPrefix(opts.prefix);
    options.sinkOptions->setup(this);
}

void Logger::reconfigure(const std::vector<std::string>& selectors) {
	LogOptions o(options);
    o.selectors = selectors;
    o.deselectors.clear();
    select(Selector(o));
    options = o;                // Don't update options till selectors has been validated.
}

void Logger::setPrefix(const std::string& p) { prefix = p; }


bool Logger::getHiresTimestamp()
{
    return flags & HIRES;
}


void Logger::setHiresTimestamp(bool setting)
{
	Mutex::ScopedLock l(lock);
    if (setting)
        flags |= HIRES;
    else
        flags &= ~HIRES;
}

}} // namespace qpid::log
