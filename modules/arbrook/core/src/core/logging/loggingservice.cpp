#include "core/logging/loggingservice.hpp"

namespace rythe::core
{
	void LoggingService::initialize()
	{
		log::setup();
		log::info("Logging Initialized");
	}

	void LoggingService::update()
	{

	}

	void LoggingService::shutdown()
	{
		log::info("Shutting Down Logging");
	}
}