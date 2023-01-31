#include "systems/testsystem.hpp"
#include "logging/logging.hpp"

namespace rythe::core
{
	void TestSystem::setup()
	{
		log::debug("Test System setup");
		ecs::Registry::registerComponent<exampleComp>();
		for (int i = 0; i < 10; i++)
		{
			auto& ent = createEntity();
			auto& comp = ent.addComponent<exampleComp>();
			log::debug("//");
			log::debug(ent.m_name);
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
		log::debug("Test System shutdown");
	}
}