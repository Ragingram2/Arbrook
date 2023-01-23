#include "events/eventbus.hpp"

namespace rythe::core::events
{
	void EventBus::initialize()
	{

	}

	void EventBus::update()
	{

	}

	void EventBus::kill()
	{

	}

	void EventBus::raiseEvent(event_base& value)
	{
		if (m_callbacks.contains(value.get_id()))
		{
			m_callbacks.at(value.get_id())(value);
		}
	}
}