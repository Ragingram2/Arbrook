#include "systems/testsystem.hpp"
#include "logging/logging.hpp"

namespace rythe::core
{
	void TestSystem::setup()
	{
		log::debug("Test System setup");
		for (int i = 0; i < 10; i++)
		{
			auto& ent = createEntity();
			ent.addComponent<exampleComp>();
			log::debug("//");
			log::debug(ent.m_name);
			auto& comp = ent.getComponent<exampleComp>();
			log::debug(comp.i);
			comp.i = i;
			log::debug(comp.i);
		}
	}

	void TestSystem::update()
	{

	}

	void TestSystem::shutdown()
	{
		log::debug(ecs::Registry::m_entities.size());
		for (int i = 1; i <= 10; i++)
		{
			auto& ent = ecs::Registry::m_entities[i];
			log::debug("//");
			log::debug(ent.m_name);
			log::debug(ent.m_id);
			destroyEntity(ent);
		}
		log::debug(ecs::Registry::m_entities.size());
		log::debug("Test System shutdown");
	}
}