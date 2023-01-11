#pragma once
#include <memory>
#include <unordered_map>

#include "engine/services/service.hpp"
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
		void bindToEvent(id_type id, const delegate<void(event_base&)>& callback);
		void bindToEvent(id_type id, delegate<void(event_base&)>&& callback);
		void unbindFromEvent(id_type id, const delegate<void(event_base&)>& callback);
	};
}