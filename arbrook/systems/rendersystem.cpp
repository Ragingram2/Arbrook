#include "systems/rendersystem.hpp"

namespace rythe::rendering
{
	void RenderSystem::setup()
	{
		core::log::debug("Render System setup");
		window.create(sf::VideoMode(720, 640), "SFML works!");
	}

	void RenderSystem::update()
	{
		if (!window.isOpen())
			return;

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

		window.clear(sf::Color::Black);
		for (auto& [id, ent] : m_filter.m_entities)
		{
			auto& renderComp = ent.getComponent<core::renderComp>();
			auto& transform = ent.getComponent<core::transform>();

			if (renderComp.draw)
			{
				auto& sprite = renderComp.sprite;
				sprite.setPosition(transform.position);
				sprite.setScale(transform.scale);
				sprite.setRotation(transform.rotation);
				sprite.setFillColor(renderComp.color);
				sprite.setRadius(renderComp.radius);
				window.draw(sprite);
			}
		}
		window.display();
	}

	void RenderSystem::shutdown()
	{
		window.close();
	}
}