#include "modules/module.hpp"
#pragma once

namespace rythe::core
{
	template<typename systemType>
	void Module::reportSystem()
	{
		auto [iter, elem] = m_systems.emplace(rsl::typeHash<systemType>(), std::make_unique<systemType>());
		systemType& _system = *static_cast<systemType*>(iter->second.get());
		m_initFuncs.push_back<systemType, &systemType::setup>(_system);
		m_updateFuncs.push_back<systemType, &systemType::update>(_system);
		m_shutdownFuncs.push_back<systemType, &systemType::shutdown>(_system);
	}
}
