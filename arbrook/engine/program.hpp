#pragma once
#include <memory>
#include <unordered_map>
#include <iostream>

#include "engine/services/service.hpp"
#include "engine/services/serviceregistry.hpp"
#include "platform/platform.hpp"
#include "types/primitives.hpp"

namespace rythe::core
{
	class Program
	{
	private:
		ServiceRegistry* m_registry;
	public:
		bool m_running = true;

		Program(ServiceRegistry& registry)
		{
			m_registry = &registry;
		};
		~Program() = default;

		void initialize();
		void update();
		void kill();
	};
}