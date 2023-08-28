#pragma once
#include <memory>
#include <stack>
#include <unordered_map>
#include <functional>

#include <rsl/delegate>
#include <rsl/primitives>

#include "core/engine/services/service.hpp"
#include "core/logging/logging.hpp"
#include "core/events/event.hpp"

namespace rythe::core::events
{
	class EventBus : public Service
	{
	public:
		using listenerFunc = void(events::event_base&);
		using listenerDelegate = rsl::delegate<listenerFunc>;
	private:
		static std::unordered_map<rsl::id_type, rsl::multicast_delegate<listenerFunc>> m_callbacks;
		static std::stack<std::pair<rsl::multicast_delegate<listenerFunc>, event_base*>> m_eventQueue;
	public:
		void initialize() override;
		void update() override;
		void shutdown() override;

		static void raiseEvent(event_base& value, bool immediate = false);

		template <typename event_type, typename owner_type, void(owner_type::* func_type)(event_type&)>
		static void bind(owner_type& instance);
		template <typename event_type>
		static void bind(const rsl::delegate<void(event_type&)>& func);
		template <typename event_type>
		static void bind(rsl::delegate<void(event_type&)>&& func);
		template<typename event_type>
		static void unbind(const rsl::delegate<void(event_type&)>& func);
		template<typename event_type>
		static void unbind(rsl::delegate<void(event_type&)>&& func);

		template<typename event_type, typename... Args>
		static void raiseEvent(Args&&... args);
	};
}

#include "core/events/eventbus.inl"