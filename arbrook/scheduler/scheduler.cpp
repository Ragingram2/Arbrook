#include "scheduler/scheduler.hpp"

namespace rythe::core::scheduling
{
	void Scheduler::initialize()
	{
		m_initFuncs();
	}

	void Scheduler::update()
	{
		if (m_running)
			m_updateFuncs();
	}

	void Scheduler::shutdown()
	{
		log::debug("Scheduler shutting down");
		m_shutdownFuncs();

		m_initFuncs.clear();
		m_updateFuncs.clear();
		m_shutdownFuncs.clear();

		m_modules.clear();
	}
}