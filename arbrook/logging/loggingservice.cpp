#include "logging/loggingservice.hpp"

namespace rythe::core
{
	void LoggingService::initialize()
	{
		rythe::core::log::setup();
		log::debug("Logging Initialized");
	}

	void LoggingService::update()
	{
		//std::cout << "Program service tick" << std::endl;
	}

	void LoggingService::shutdown()
	{
		log::debug("Logging Shutdown");
	}
}