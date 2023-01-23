#include "systems/testsystem.hpp"
#include "logging/logging.hpp"

namespace rythe::core
{
	void TestSystem::setup()
	{
		log::debug("Test System setup");

		for (int i = 0; i < 100; i++)
		{
			createEntity();
		}

		for (auto& [id, ent] : ecs::Registry::m_entities)
		{
			log::debug("Entity: {}", ent.m_name);
		}
	}

	void TestSystem::update()
	{
		log::debug("Test System update");
	}

	void TestSystem::shutdown()
	{
		log::debug("Test System shutdown");
	}
}