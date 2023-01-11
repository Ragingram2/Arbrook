#include "engine/program.hpp"
#include "logging/loggingservice.hpp"

namespace rythe::core
{
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
}