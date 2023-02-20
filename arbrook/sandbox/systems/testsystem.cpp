#include "sandbox/systems/testsystem.hpp"

namespace rythe::core
{
	void TestSystem::setup()
	{
		log::info("Initializing Test System");
		float spawnCount = 1000.f;
		for (int i = 0; i < spawnCount; i++)
		{
			auto& ent = createEntity();
			auto& render = ent.addComponent<renderComp>();

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
		log::info("Shutting down Test System ");
	}
}