#include "events/eventbus.hpp"
#pragma once

namespace rythe::core::events
{

	template <typename event_type, typename owner_type, void(owner_type::* func_type)(event_type&)>
	R_ALWAYS_INLINE void EventBus::bind()
	{
		auto temp = rsl::delegate<void(event_type&)>::template from<owner_type, func_type>(owner_type::Instance());
		auto& del = reinterpret_cast<rsl::delegate<void(events::event_base&)>&&>(std::move(temp));
		m_binds[event_type::id].push_back(reinterpret_cast<const rsl::delegate<void(event_base&)>&>(del));
	}

	template <typename event_type>
	R_ALWAYS_INLINE void EventBus::bind(const rsl::delegate<void(event_type&)>& func)
	{
		m_callbacks[event_type::id].push_back(*reinterpret_cast<const rsl::delegate<void(events::event_base&)>*>(&func));
	}

	template <typename event_type>
	R_ALWAYS_INLINE void EventBus::bind(rsl::delegate<void(event_type&)>&& func)
	{
		m_callbacks[event_type::id].push_back(*reinterpret_cast<rsl::delegate<void(events::event_base&)>*>(&func));
	}

	template<typename event_type>
	R_ALWAYS_INLINE void EventBus::unbind(const rsl::delegate<void(event_type&)>& func)
	{
		m_callbacks.at(event_type::id).erase(*reinterpret_cast<const rsl::delegate<void(events::event_base&)>*>(&func));
	}

	template<typename event_type>
	R_ALWAYS_INLINE void EventBus::unbind(rsl::delegate<void(event_type&)>&& func)
	{
		m_callbacks.at(event_type::id).erase(*reinterpret_cast<rsl::delegate<void(events::event_base&&)>*>(&func));
	}
}
