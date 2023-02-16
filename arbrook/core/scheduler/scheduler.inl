#include "core/scheduler/scheduler.hpp"
#pragma once

namespace rythe::core::scheduling
{
	template<typename moduleType>
	void Scheduler::reportModule()
	{
		auto [iter, elem] = m_modules.emplace(rsl::typeHash<moduleType>(), std::make_unique<moduleType>());
		Module& _module = *static_cast<Module*>(iter->second.get());
		m_initFuncs.push_back<Module, &Module::onInitialize>(_module);
		m_updateFuncs.push_back<Module, &Module::onUpdate>(_module);
		m_shutdownFuncs.push_back<Module, &Module::onShutdown>(_module);
	}
}