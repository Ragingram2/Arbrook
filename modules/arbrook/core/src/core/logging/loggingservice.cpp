#include "loggingservice.hpp"

namespace rythe::core
{
	void LoggingService::initialize()
	{
		auto& instance = rsl::log::impl::get();
		appConsoleSink.get()->set_level(spdlog::level::trace);
		instance.logger->sinks().push_back(appConsoleSink);
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