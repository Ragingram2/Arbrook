#pragma once
#include <memory>
#include <unordered_map>
#include <iostream>

#include <rsl/primitives>
#include <rsl/utilities>

#include "core/engine/services/service.hpp"
#include "core/engine/services/serviceregistry.hpp"
#include "core/events/eventbus.hpp"
#include "core/events/defaults/exit_event.hpp"

//I should probably change these to work with delegates as well, avoid more pointer indirections
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