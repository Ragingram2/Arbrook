#include "modules/rendermodule.hpp"

namespace rythe::rendering
{
	void RenderModule::initialize()
	{
		window.create(sf::VideoMode(200, 200), "SFML works!");
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
			}
		}
	}

	void RenderModule::shutdown()
	{

	}
}