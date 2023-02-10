#pragma once
#include <memory>
#include <stack>
#include <unordered_map>
#include <functional>

#include <rythe/delegate>
#include <rythe/primitives>

#include "engine/services/service.hpp"
#include "logging/logging.hpp"
#include "platform/platform.hpp"
#include "events/event.hpp"

namespace rythe::core::events
{
	class EventBus : public Service
	{
	public:
		using listenerFunc = void(events::event_base&);
		using listenerDelegate = rsl::delegate<listenerFunc>;
	private:
		std::unordered_map<rsl::id_type, rsl::multicast_delegate<listenerFunc>> m_callbacks;
		std::stack<std::pair<rsl::multicast_delegate<listenerFunc>, event_base*>> m_eventQueue;
	public:
		void initialize() override;
		void update() override;
		void shutdown() override;

		void raiseEvent(event_base& value);

		template <typename event_type, typename owner_type, void(owner_type::* func_type)(event_type&)>
		R_ALWAYS_INLINE void bind();
		template <typename event_type>
		R_ALWAYS_INLINE void bind(const rsl::delegate<void(event_type&)>& func);
		template <typename event_type>
		R_ALWAYS_INLINE void bind(rsl::delegate<void(event_type&)>&& func);
		template<typename event_type>
		R_ALWAYS_INLINE void unbind(const rsl::delegate<void(event_type&)>& func);
		template<typename event_type>
		R_ALWAYS_INLINE void unbind(rsl::delegate<void(event_type&)>&& func);
	};
}

#include "events/eventbus.inl"