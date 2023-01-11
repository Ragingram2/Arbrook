#include "modules/rendermodule.hpp"
#include "events/eventbus.hpp"
#include "events/defaults/exit_event.hpp"

namespace rythe::rendering
{
	void RenderModule::initialize()
	{
		window.create(sf::VideoMode(720, 640), "SFML works!");
	}

	void RenderModule::update()
	{
		window.clear();
		window.display();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				rythe::core::events::exit evt(0);
				rythe::core::Program::Instance().m_registry->get_service<rythe::core::events::EventBus>()->raiseEvent(evt);
			}
		}
	}

	void RenderModule::shutdown()
	{

	}
}