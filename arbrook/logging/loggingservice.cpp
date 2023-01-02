#include "logging/loggingservice.hpp"

namespace rythe::core
{
	void LoggingService::initialize()
	{
		//std::cout << "Initializing Logging" << std::endl;
		rythe::core::log::setup();
	}

	void LoggingService::update()
	{
		//std::cout << "Program service tick" << std::endl;
	}

	void LoggingService::kill()
	{
		//std::cout << "Killing Program service " << std::endl;
	}
}