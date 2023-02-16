#include "sandbox/systems/flipsystem.hpp"

namespace rythe::core
{
	void FlipSystem::setup()
	{
		log::debug("Flip System setup");
		float spawnCount = 1000.f;
		for (int i = 0; i < spawnCount; i++)
		{
			auto& ent = createEntity();
			auto& render = ent.addComponent<renderComp>();
			render.color = sf::Color::Blue;
			render.radius = 1.0f;

			auto& transf = ent.addComponent<transform>();
			float x = std::rand() % 720;
			float y = std::rand() % 640;
			transf.position = math::vec2(x, y);

			ent.addComponent<rigidbody>();
		}
	}

	void FlipSystem::update()
	{
		for (auto& ent : m_filter)
		{
			auto& transf = ent.getComponent<transform>();
			auto& rb = ent.getComponent<rigidbody>();
			rb.prevVelocity = rb.velocity;
			rb.velocity += m_gravity * .02f;
			transf.position += rb.velocity * .02f;
		}
	}

	void FlipSystem::shutdown()
	{
		log::debug("Flip System shutdown");
	}
}