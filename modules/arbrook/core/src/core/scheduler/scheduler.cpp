#include "scheduler.hpp"

namespace rythe::core::scheduling
{
	void Scheduler::initialize()
	{
		m_initialize = true;
		log::info("Initializing Scheduler");
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
		log::info("Shutting Down Scheduler");
		m_shutdownFuncs();

		m_initFuncs.clear();
		m_updateFuncs.clear();
		m_shutdownFuncs.clear();

		m_modules.clear();
	}
}