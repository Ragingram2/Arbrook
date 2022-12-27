#include <iostream>
#include <SFML/Graphics.hpp>

#include "engine/program.hpp"

using namespace rythe::core;




int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);
	ServiceRegistry registry;
	registry.register_service<Service>();
	Program program(registry);
	program.initialize();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				program.kill();
				window.close();
			}
		}

		window.clear();
		window.display();

		program.update();
	}

	return 0;
}


