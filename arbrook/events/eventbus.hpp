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
		std::unordered_map<id_type, std::vector<std::function<void(event_base&)>>> m_callbacks;
	public:
		void initialize() override;
		void update() override;
		void kill() override;

		void raiseEvent(event_base& value);

		template <typename event_type>
		inline void insert_back(const std::function<void(event_base&)>& func)
		{
			m_callbacks[event_type::id].push_back(func);
		}

		template <typename event_type>
		inline void insert_back(std::function<void(event_base&)>&& func)
		{
			m_callbacks[event_type::id].push_back(func);
		}
	};
}

#include "events/eventbus.inl"