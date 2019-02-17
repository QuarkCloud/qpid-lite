
#include "qpid/amqp0_10/EngineInit.h"
#include "qpid/amqp0_10/ConnectionImpl.h"
#include "qpid/driver/ConnectionImpl.h"
#include "qpid/amqp/ProtocolRegistry.h"
#include "qpid/amqp/DriverImpl.h"

namespace qpid {
	namespace amqp0_10 {
		namespace {
			amqp::ConnectionImpl* create(const std::string& u, const qpid::types::Variant::Map& o)
			{
				try {
					return new ConnectionImpl(u, o);
				}
				catch (const types::Exception&) {
					throw;
				}
				catch (const qpid::sys::Exception& e) {
					throw amqp::ConnectionError(e.what());
				}
			}

			void shutdown()
			{
				driver::shutdown();
			}
		}

		void EngineInit()
		{
			amqp::ProtocolRegistry::add("amqp0-10", &create, &shutdown);
		}
	}
}