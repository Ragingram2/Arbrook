#include "module.hpp"

namespace rythe::core
{
	void Module::onInitialize()
	{
		//Module Setup
		setup();
		m_initialize = true;
		//m_initFuncs();
	}

	void Module::onUpdate()
	{
		if (m_initialize)
		{
			m_initFuncs();
			m_initialize = false;
			return;
		}

		//Module Update
		update();
		m_updateFuncs();
	}

	void Module::onShutdown()
	{
		//Module Shutdown
		shutdown();
		m_shutdownFuncs();
	}
}