#include "events/eventbus.hpp"
#pragma once

namespace rythe::core::events
{

	template <typename event_type, typename owner_type, void(owner_type::* func_type)(event_type&)>
	inline void EventBus::bind(owner_type& instance)
	{
		auto temp = rsl::delegate<void(event_type&)>::template create<owner_type, func_type>(instance);
		m_callbacks[event_type::id].push_back(rsl::force_cast<listenerDelegate>(temp));
	}

	template <typename event_type>
	inline void EventBus::bind(const rsl::delegate<void(event_type&)>& func)
	{
		m_callbacks[event_type::id].push_back(rsl::force_cast<listenerDelegate>(&func));
	}

	template <typename event_type>
	inline void EventBus::bind(rsl::delegate<void(event_type&)>&& func)
	{
		m_callbacks[event_type::id].push_back(rsl::force_cast<listenerDelegate>(&func));
	}

	template<typename event_type>
	inline void EventBus::unbind(const rsl::delegate<void(event_type&)>& func)
	{
		m_callbacks[event_type::id].erase(rsl::force_cast<listenerDelegate>(&func));
	}

	template<typename event_type>
	inline void EventBus::unbind(rsl::delegate<void(event_type&)>&& func)
	{
		m_callbacks[event_type::id].erase(rsl::force_cast<listenerDelegate>(&func));
	}

	template<typename event_type, typename... Args>
	inline void EventBus::raiseEvent(Args&&... args)
	{
		if (m_callbacks.contains(event_type::id))
		{
			event_type event(args...);
			rsl::force_cast<rsl::multicast_delegate<void(event_type&)>>(m_callbacks.at(event_type::id))(event);
		}
	}
}
