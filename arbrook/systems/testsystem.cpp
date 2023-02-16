#include "systems/testsystem.hpp"

namespace rythe::core
{
	void TestSystem::setup()
	{
		log::debug("Test System setup");
		float spawnCount = 1000.f;
		for (int i = 0; i < spawnCount; i++)
		{
			auto& ent = createEntity();
			auto& render = ent.addComponent<renderComp>();
			float normal = i / 10.0f;
			render.color = sf::Color(normal * 255.0f, (1.0f - normal) * 255.0f, (.5f - normal) * 255.0f);
			render.radius = 5.0f;

			auto& transf = ent.addComponent<transform>();
			float randX = std::rand() % 720;
			float randY = std::rand() % 640;
			transf.position = math::vec2(randX, randY);
		}
	}

	void TestSystem::update()
	{
		for (auto& ent : m_filter)
		{
			auto& transf = ent.getComponent<transform>();
			transf.position += math::vec2(.08f, 0);

			if (transf.position.x > 730)
			{
				transf.position.x = -10.0f;
			}
		}
	}

	void TestSystem::shutdown()
	{
		log::debug("Test System shutdown");
	}
}