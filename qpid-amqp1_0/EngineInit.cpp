
#include "qpid/amqp1_0/EngineInit.h"
#include "qpid/amqp1_0/ConnectionImpl.h"
#include "qpid/driver/ConnectionImpl.h"
#include "qpid/amqp/ProtocolRegistry.h"
#include "qpid/amqp/DriverImpl.h"

namespace qpid {
	namespace amqp1_0 {
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
				amqp::DriverImpl::getDefault()->stop();
			}
		}

		void EngineInit()
		{
			amqp::ProtocolRegistry::add("amqp1.0", &create, &shutdown);
		}
	}
}