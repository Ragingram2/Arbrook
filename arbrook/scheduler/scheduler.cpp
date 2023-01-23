#include "scheduler/scheduler.hpp"

namespace rythe::core::scheduling
{
	void Scheduler::initialize()
	{
		m_initFuncs();
	}

	void Scheduler::update()
	{
		m_updateFuncs();
	}

	void Scheduler::shutdown()
	{
		log::debug("Scheduler shutting down");
		m_shutdownFuncs();
	}
}