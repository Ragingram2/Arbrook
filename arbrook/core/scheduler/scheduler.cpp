#include "core/scheduler/scheduler.hpp"

namespace rythe::core::scheduling
{
	void Scheduler::initialize()
	{
		/*m_initFuncs();*/
		m_initialize = true;
	}

	void Scheduler::update()
	{
		if (!m_running)
			return;

		if (m_initialize)
		{
			m_initFuncs();
			m_initialize = false;
			return;
		}

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