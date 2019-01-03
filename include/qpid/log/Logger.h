#ifndef QPID_LOG_LOGGER_H
#define QPID_LOG_LOGGER_H

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

#include "qpid/log/Selector.h"
#include "qpid/log/Options.h"
#include "qpid/sys/Mutex.h"
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/noncopyable.hpp>
#include <set>
#include "qpid/log/Compile.h"

namespace qpid {
namespace log {

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
class QPID_LOG_CLASS_EXTERN Logger : private boost::noncopyable {
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
		QPID_LOG_EXTERN Output();
		QPID_LOG_EXTERN virtual ~Output();
        /** Receives the statemnt of origin and formatted message to log. */
        virtual void log(const Statement&, const std::string&) =0;
    };

	QPID_LOG_EXTERN static Logger& instance();

	QPID_LOG_EXTERN Logger();
	QPID_LOG_EXTERN ~Logger();

    /** Select the messages to be logged. */
	QPID_LOG_EXTERN void select(const Selector& s);

    /** Set the formatting flags, bitwise OR of FormatFlag values. */
	QPID_LOG_EXTERN void format(int formatFlags);

    /** Set format flags from options object.
     *@returns computed flags.
     */
	QPID_LOG_EXTERN int format(const Options&);

    /** Configure logger from Options */
	QPID_LOG_EXTERN void configure(const Options& o);

    /** Reset the log selectors */
	QPID_LOG_EXTERN void reconfigure(const std::vector<std::string>& selectors);

    /** Add a statement. */
	QPID_LOG_EXTERN void add(Statement& s);

    /** Log a message. */
	QPID_LOG_EXTERN void log(const Statement&, const std::string&);

    /** Add an output destination for messages */
	QPID_LOG_EXTERN void output(std::auto_ptr<Output> out);

    /** Set a prefix for all messages */
	QPID_LOG_EXTERN void setPrefix(const std::string& prefix);

    /** Reset the logger. */
	QPID_LOG_EXTERN void clear();

    /** Get the options used to configure the logger. */
    QPID_LOG_INLINE_EXTERN const Options& getOptions() const { return options; }

    /** Get the hires timestamp setting */
	QPID_LOG_EXTERN bool getHiresTimestamp();

    /** Set the hires timestamp setting */
	QPID_LOG_EXTERN void setHiresTimestamp(bool setting);

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
    Options options;
};

}} // namespace qpid::log


#endif  /*!QPID_LOG_LOGGER_H*/
