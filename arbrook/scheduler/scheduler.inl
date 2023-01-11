#include "scheduler.hpp"
#pragma once

namespace rythe::core::scheduling
{
	template<typename moduleType>
	void Scheduler::reportModule()
	{
		auto [iter, elem] = m_modules.emplace(typeHash<moduleType>(), std::make_unique<moduleType>());
		moduleType* _module = static_cast<moduleType*>(iter->second.get());
		m_initFuncs.insert_back<moduleType,&moduleType::initialize>(_module);
		m_updateFuncs.insert_back<moduleType, &moduleType::update>(_module);
	}
}