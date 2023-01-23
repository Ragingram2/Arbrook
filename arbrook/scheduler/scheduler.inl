#include "scheduler.hpp"
#pragma once

namespace rythe::core::scheduling
{
	template<typename moduleType>
	void Scheduler::reportModule()
	{
		auto [iter, elem] = m_modules.emplace(typeHash<moduleType>(), std::make_unique<moduleType>());
		moduleType& _module = *static_cast<moduleType*>(iter->second.get());
		m_initFuncs.push_back<moduleType, &moduleType::initialize>(_module);
		m_updateFuncs.push_back<moduleType, &moduleType::update>(_module);
		m_shutdownFuncs.push_back<moduleType, &moduleType::shutdown>(_module);
	}
}