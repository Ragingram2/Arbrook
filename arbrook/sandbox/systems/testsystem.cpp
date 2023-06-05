#include "sandbox/systems/testsystem.hpp"
namespace rythe::core
{

	void TestSystem::setup()
	{
		log::info("Initializing Test System");

		auto wId = registry->m_worldId;
		m_api = &registry->m_entities[wId].getComponent<gfx::RenderInterface>();

		m_api->makeCurrent();
	}

	void TestSystem::update()
	{
		m_api->pollEvents();
	}

	void TestSystem::shutdown()
	{
		log::info("Shutting down Test System ");
	}
}