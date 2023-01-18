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
		log::debug("Raising Event");
		if (m_callbacks.contains(value.get_id()))
		{
			log::debug("Event Found");
			for (auto& func : m_callbacks.at(value.get_id()))
			{
				log::debug("calling func");
				func(value);
			}
		}
	}


}