#include "events/eventbus.hpp"

namespace rythe::core::events
{
	void EventBus::initialize()
	{
		log::debug("Eventbus Initialized");
	}

	void EventBus::update()
	{
		while (m_eventQueue.size() > 0)
		{
			auto& pair = m_eventQueue.top();
			pair.first(*pair.second);
			m_eventQueue.pop();
		}
	}

	void EventBus::shutdown()
	{
		m_callbacks.clear();
		log::debug("Eventbus Shutdown");
	}

	void EventBus::raiseEvent(event_base& value, bool immediate)
	{
		if (m_callbacks.contains(value.get_id()))
		{
			if (immediate)
				m_callbacks.at(value.get_id())(value);
			else
				m_eventQueue.push(std::make_pair(m_callbacks.at(value.get_id()), &value));
		}
	}
}