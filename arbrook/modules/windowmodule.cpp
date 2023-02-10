#include "modules/windowmodule.hpp"


namespace rythe::window
{
	void WindowModule::setup()
	{
		window.create(sf::VideoMode(720, 640), "SFML works!");
	}

	void WindowModule::update()
	{
		if (!window.isOpen())
			return;

		window.clear();
		window.display();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				rythe::core::events::exit evt(0);
				rythe::core::Program::Instance().m_registry->get_service<rythe::core::events::EventBus>()->raiseEvent(evt);
				break;
			}
		}
	}

	void WindowModule::shutdown()
	{
		window.close();
	}
}