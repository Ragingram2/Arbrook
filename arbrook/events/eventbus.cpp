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
			m_callbacks.at(value.get_id()).invoke(value);
		}
	}

	void EventBus::bindToEvent(id_type id, const delegate<void(event_base&)>& callback)
	{
		m_callbacks.try_emplace(id).first->second.push_back(callback);
	}

	void EventBus::bindToEvent(id_type id, delegate<void(event_base&)>&& callback)
	{
		m_callbacks.try_emplace(id).first->second.push_back(callback);
	}

	void EventBus::unbindFromEvent(id_type id, const delegate<void(event_base&)>& callback)
	{
		m_callbacks.at(id).erase(callback);
	}
}