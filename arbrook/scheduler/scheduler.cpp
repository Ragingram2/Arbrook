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

	void Scheduler::kill()
	{

	}
}