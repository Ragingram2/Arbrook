#pragma once
#include <memory>
#include <stack>
#include <unordered_map>
#include <functional>

#include <rythe/delegate>
#include <rythe/primitives>

#include "core/engine/services/service.hpp"
#include "core/logging/logging.hpp"
#include "core/platform/platform.hpp"
#include "core/events/event.hpp"

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

		void raiseEvent(event_base& value, bool immediate = false);

		template <typename event_type, typename owner_type, void(owner_type::* func_type)(event_type&)>
		void bind(owner_type& instance);
		template <typename event_type>
		void bind(const rsl::delegate<void(event_type&)>& func);
		template <typename event_type>
		void bind(rsl::delegate<void(event_type&)>&& func);
		template<typename event_type>
		void unbind(const rsl::delegate<void(event_type&)>& func);
		template<typename event_type>
		void unbind(rsl::delegate<void(event_type&)>&& func);

		template<typename event_type, typename... Args>
		void raiseEvent(Args&&... args);
	};
}

#include "core/events/eventbus.inl"