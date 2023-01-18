#include "engine/program.hpp"
#include "logging/loggingservice.hpp"

namespace rythe::core
{
	ServiceRegistry* Program::m_registry;

	void Program::initialize()
	{
		for (auto& [id, service] : m_registry->m_services)
		{
			if (service)
			{
				service->initialize();
			}
		}
		log::info("Program initialized");
	}

	void Program::update()
	{
		for (auto& [id, service] : m_registry->m_services)
		{
			if (service)
			{
				service->update();
			}
		}
	}

	void Program::kill()
	{
		log::info("Killing Program");
		for (auto& [id, service] : m_registry->m_services)
		{
			if (service)
			{
				service->kill();
			}
		}
	}

	void Program::exit(events::exit& evt)
	{
		log::debug("STOP");
		m_running = false;
	}
}