#include "systems/testsystem.hpp"

namespace rythe::core
{
	void TestSystem::setup()
	{
		log::debug("Test System setup");
		for (int i = 0; i < 10; i++)
		{
			auto& ent = createEntity();
			auto& render = ent.addComponent<renderComp>();
			render.color = sf::Color((i / 10.0f) * 255.0f, (1.0f - (i / 10.0f)) * 255.0f, (.5f - (i / 10.0f)) * 255.0f);
			render.radius = 5.0f;

			auto& transf = ent.addComponent<transform>();
			transf.position = math::vec2(10, 5 + i * 63);
		}
	}

	void TestSystem::update()
	{
		for (auto& [id, ent] : m_filter.m_entities)
		{
			auto& transf = ent.getComponent<transform>();
			transf.position += math::vec2(.08f, 0);

			if (transf.position.x > 700)
			{
				transf.position.x = 0.0f;
			}
		}
	}

	void TestSystem::shutdown()
	{
		log::debug("Test System shutdown");
	}
}