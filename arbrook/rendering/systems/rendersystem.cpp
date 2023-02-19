#include "rendering/systems/rendersystem.hpp"

namespace rythe::rendering
{
	void Renderer::setup()
	{
		core::log::debug("Render System setup");
		window.create(sf::VideoMode(720, 640), "SFML works!");
	}

	void Renderer::update()
	{
		if (!window.isOpen())
			return; 

		sf::Event event;
		if (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				rythe::core::events::exit evt(0);
				raiseEvent(evt);
				return;
			}
		}

		//window.clear(sf::Color::Black);
		//for (auto& ent : m_filter)
		//{
		//	auto& renderComp = ent.getComponent<core::renderComp>();
		//	auto& transform = ent.getComponent<core::transform>();

		//	if (renderComp.draw)
		//	{
		//		auto& sprite = renderComp.sprite;
		//		sprite.setPosition(transform.position.x, transform.position.y);
		//		sprite.setScale(transform.scale.x, transform.scale.y);
		//		sprite.setRotation(transform.rotation);
		//		sprite.setFillColor(renderComp.color);
		//		sprite.setRadius(renderComp.radius);
		//		window.draw(sprite);
		//	}
		//}
		//window.display();
	}



	void Renderer::shutdown()
	{
		window.close();
	}
}