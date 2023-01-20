#pragma once
#include <memory>
#include <unordered_map>
#include <functional>

#include "engine/services/service.hpp"
#include "logging/logging.hpp"
#include "platform/platform.hpp"
#include "containers/delegate.hpp"
#include "types/types.hpp"
#include "events/event.hpp"

namespace rythe::core::events
{
	class EventBus : public Service
	{
	private:
		std::unordered_map<id_type, multicast_delegate<void(event_base&)>> m_callbacks;
	public:
		void initialize() override;
		void update() override;
		void kill() override;

		void raiseEvent(event_base& value);


		template <typename event_type,typename owner_type, void(owner_type::* func_type)(event_type&)>
		R_ALWAYS_INLINE void bind();
		template <typename event_type>
		R_ALWAYS_INLINE void bind(const delegate<void(event_type&)>& func);
		template <typename event_type>
		R_ALWAYS_INLINE void bind(delegate<void(event_type&)>&& func);
		template<typename event_type>
		R_ALWAYS_INLINE void unbind(const delegate<void(event_type&)>& func);
		template<typename event_type>
		R_ALWAYS_INLINE void unbind(delegate<void(event_type&)>&& func);
	};
}

#include "events/eventbus.inl"