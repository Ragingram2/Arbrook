#include "modules/module.hpp"
#pragma once

namespace rythe::core
{
	template<typename systemType>
	void Module::reportSystem()
	{
		auto [iter, elem] = m_systems.emplace(typeHash<systemType>(), std::make_unique<systemType>());
		//systemType* _module = static_cast<systemType*>(iter->second.get());
		m_initFuncs += &systemType::initialize;
		m_updateFuncs += &systemType::update;
		m_shutdownFuncs += &systemType::shutdown;
		//m_initFuncs.insert_back<systemType, &systemType::initialize>(_module);
		//m_updateFuncs.insert_back<systemType, &systemType::update>(_module);
		//m_shutdownFuncs.insert_back<systemType, &systemType::shutdown>(_module);
	}
}
