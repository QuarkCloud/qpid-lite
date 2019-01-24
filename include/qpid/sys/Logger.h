#ifndef QPID_SYS_LOGGER_H
#define QPID_SYS_LOGGER_H 1

/*
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "qpid/sys/Selector.h"
#include "qpid/sys/Mutex.h"
#include "qpid/sys/Options.h"
#include "qpid/sys/SinkOptions.h"
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/noncopyable.hpp>
#include <set>
#include "qpid/sys/Compile.h"

namespace qpid {
namespace sys {

	/** Logging options for config parser. */
	struct LogOptions : public qpid::sys::Options {
		/** Pass argv[0] for use in syslog output */
		QPID_SYS_EXTERN LogOptions(const std::string& argv0_ = std::string(),
			const std::string& name_ = "Logging options");
		QPID_SYS_EXTERN LogOptions(const LogOptions &);

		QPID_SYS_EXTERN LogOptions& operator=(const LogOptions&);

		std::string argv0;
		std::string name;
		std::vector<std::string> selectors;
		std::vector<std::string> deselectors;
		bool time, level, thread, source, function, hiresTs, category;
		bool trace;
		std::string prefix;
		std::auto_ptr<SinkOptions> sinkOptions;
	};

	/** Get a string list of the allowed levels */
	QPID_SYS_EXTERN std::string getLevels();

	/** Get a string list of the allowed categories */
	QPID_SYS_EXTERN std::string getCategories();


/**
 * Central logging agent.
 *
 * Thread safe, singleton.
 *
 * The Logger provides all needed functionality for selecting and
 * formatting logging output. The actual outputting of log records
 * is handled by Logger::Output-derived classes instantiated by the
 * platform's sink-related options.
 */
class QPID_SYS_CLASS_EXTERN Logger : private boost::noncopyable {
  public:
    /** Flags indicating what to include in the log output */
    enum FormatFlag { FILE=1, LINE=2, FUNCTION=4, LEVEL=8, TIME=16, THREAD=32, HIRES=64, CATEGORY=128};

    /**
     * Logging output sink.
     *
     * The Output sink provides an interface to direct logging output to.
     * Logging sinks are primarily platform-specific as provided for on
     * each platform.
     *
     * Implementations of Output must be thread safe.
     */
    class Output {
      public:
		QPID_SYS_EXTERN Output();
		QPID_SYS_EXTERN virtual ~Output();
        /** Receives the statemnt of origin and formatted message to log. */
        virtual void log(const Statement&, const std::string&) =0;
    };

	QPID_SYS_EXTERN static Logger& instance();

	QPID_SYS_EXTERN Logger();
	QPID_SYS_EXTERN ~Logger();

    /** Select the messages to be logged. */
	QPID_SYS_EXTERN void select(const Selector& s);

    /** Set the formatting flags, bitwise OR of FormatFlag values. */
	QPID_SYS_EXTERN void format(int formatFlags);

    /** Set format flags from options object.
     *@returns computed flags.
     */
	QPID_SYS_EXTERN int format(const LogOptions&);

    /** Configure logger from Options */
	QPID_SYS_EXTERN void configure(const LogOptions& o);

    /** Reset the log selectors */
	QPID_SYS_EXTERN void reconfigure(const std::vector<std::string>& selectors);

    /** Add a statement. */
	QPID_SYS_EXTERN void add(Statement& s);

    /** Log a message. */
	QPID_SYS_EXTERN void log(const Statement&, const std::string&);

    /** Add an output destination for messages */
	QPID_SYS_EXTERN void output(std::auto_ptr<Output> out);

    /** Set a prefix for all messages */
	QPID_SYS_EXTERN void setPrefix(const std::string& prefix);

    /** Reset the logger. */
	QPID_SYS_EXTERN void clear();

    /** Get the options used to configure the logger. */
    QPID_SYS_INLINE_EXTERN const Options& getOptions() const { return options; }

    /** Get the hires timestamp setting */
	QPID_SYS_EXTERN bool getHiresTimestamp();

    /** Set the hires timestamp setting */
	QPID_SYS_EXTERN void setHiresTimestamp(bool setting);

  private:
    typedef boost::ptr_vector<Output> Outputs;
    typedef std::set<Statement*> Statements;

    sys::Mutex lock;
    inline void enable_unlocked(Statement* s);

    Statements statements;
    Outputs outputs;
    Selector selector;
    int flags;
    std::string prefix;
    LogOptions options;
};

}} // namespace qpid::log


#endif  /*!QPID_LOG_LOGGER_H*/
