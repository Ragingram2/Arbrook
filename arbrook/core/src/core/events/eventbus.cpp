#include "core/events/eventbus.hpp"

namespace rythe::core::events
{
	std::unordered_map<rsl::id_type, rsl::multicast_delegate<EventBus::listenerFunc>> EventBus::m_callbacks;
	std::stack<std::pair<rsl::multicast_delegate<EventBus::listenerFunc>, event_base*>> EventBus::m_eventQueue;
	void EventBus::initialize()
	{
		log::info("Initializing Eventbus");
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
		log::info("Shutting Down Eventbus");
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