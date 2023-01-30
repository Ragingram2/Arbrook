#include "systems/testsystem.hpp"
#include "logging/logging.hpp"

namespace rythe::core
{
	void TestSystem::setup()
	{
		log::debug("Test System setup");
		ecs::Registry::registerComponent<exampleComp>();
		auto id = rsl::typeHash<exampleComp>();
		log::debug(id);
		log::debug(ecs::Registry::m_componentFamilies[id]->m_typeId);
		auto& fam = ecs::Registry::getFamily<exampleComp>();
		log::debug(fam.m_typeId);
		for (int i = 0; i < 10; i++)
		{
			auto& ent = createEntity();
			//ent.addComponent<exampleComp>();
			//log::debug("//");
			//log::debug(ent.m_name);
			//auto& comp = ent.getComponent<exampleComp>();
			//log::debug(comp.i);
			//comp.i = i;
			//log::debug(comp.i);
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