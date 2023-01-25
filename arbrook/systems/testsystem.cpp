#include "systems/testsystem.hpp"
#include "logging/logging.hpp"

namespace rythe::core
{
	void TestSystem::setup()
	{
		log::debug("Test System setup");

		for (int i = 0; i < 100; i++)
		{
			auto& ent = createEntity();
			log::debug(ent.m_name);
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