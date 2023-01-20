#pragma once
#include "modules/module.hpp"

namespace rythe::core
{
	void Module::initialize()
	{
		m_initFuncs();
	}

	void Module::update()
	{
		m_updateFuncs();
	}

	void Module::shutdown()
	{
		m_shutdownFuncs();
	}
}