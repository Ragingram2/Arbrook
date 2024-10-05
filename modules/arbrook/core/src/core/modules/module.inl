#include "core/modules/module.hpp"
#pragma once

namespace rythe::core
{
	template<typename systemType>
	void Module::reportSystem()
	{
		auto [iter, elem] = m_systems.emplace(rsl::typeHash<systemType>(), std::make_unique<systemType>());
		systemType& _system = *static_cast<systemType*>(iter->second.get());

		if constexpr (rsl::has_setup_v<systemType, void()>)
		{
			m_initFuncs.push_back<systemType, &systemType::setup>(_system);
		}
		if constexpr (rsl::has_update_v<systemType, void()>)
		{
			m_updateFuncs.push_back<systemType, &systemType::update>(_system);
		}
		if constexpr (rsl::has_shutdown_v<systemType, void()>)
		{
			m_shutdownFuncs.push_back<systemType, &systemType::shutdown>(_system);
		}
	}
}
