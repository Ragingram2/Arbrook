#pragma once
#include <memory>
#include <unordered_map>
#include <iostream>

#include <rythe/primitives>

#include "platform/platform.hpp"
#include "engine/services/service.hpp"
#include "engine/services/serviceregistry.hpp"
#include "events/eventbus.hpp"
#include "events/defaults/exit_event.hpp"


namespace rythe::core
{
	class Program
	{
	public:
		static ServiceRegistry* m_registry;
		bool m_running = true;

		Program(ServiceRegistry& registry) 
		{
			m_registry = &registry;
		};
		~Program() = default;

		void initialize();
		void update();
		void shutdown();

		void exit(events::exit& evt);

		inline static Program& Instance(void) {
			static Program singleton(*m_registry);
			return singleton;
		}
	};
}