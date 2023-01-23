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

	void Program::shutdown()
	{
		for (auto& [id, service] : m_registry->m_services)
		{
			if (service)
			{
				service->shutdown();
			}
		}
		log::info("Killing Program");
	}

	void Program::exit(events::exit& evt)
	{
		m_running = false;
		shutdown();
	}
}