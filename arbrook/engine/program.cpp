#include "engine/program.hpp"

namespace rythe::core
{
	void Program::initialize()
	{
		std::cout << "Initializing Program" << std::endl;
		for (auto& [id, service] : m_registry->m_services)
		{
			if (service)
			{
				service->initialize();
			}
		}
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
		std::cout << "Killing Program" << std::endl;
		for (auto& [id, service] : m_registry->m_services)
		{
			if (service)
			{
				service->kill();
			}
		}
	}
}