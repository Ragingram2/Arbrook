#pragma once
#include "modules/module.hpp"

namespace rythe::core
{
	void Module::onInitialize()
	{
		//Module Setup
		setup();
		m_initFuncs();
	}

	void Module::onUpdate()
	{
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