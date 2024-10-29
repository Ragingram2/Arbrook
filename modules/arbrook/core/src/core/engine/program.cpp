#include "../engine/program.hpp"
#include "../logging/loggingservice.hpp"


namespace rythe::core
{
	ServiceRegistry* Program::m_registry;

	void Program::initialize()
	{
		std::cout << "Program initialized\n";
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
			if (!m_running)
				break;

			if (service && service->m_running)
			{
				service->update();
			}
		}
	}

	void Program::shutdown()
	{
		for (auto& [id, service] : m_registry->m_services)
		{
			if (service && service->m_running)
			{
				service->m_running = false;
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