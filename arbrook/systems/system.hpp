#pragma once
#include "platform/platform.hpp"
#include "ecs/registry.hpp"
#include "engine/program.hpp"

namespace rythe::core
{
	class System
	{
	public:
		static ecs::Registry* registry;
		System() = default;
		virtual ~System() = default;

		virtual void setup();
		virtual void update() {};
		virtual void shutdown() {};

		ecs::entity createEntity();
		ecs::entity createEntity(std::string name);
		void destroyEntity(ecs::entity& ent);
		void destroyEntity(rsl::id_type id);
	};
}

#include "systems/system.inl"
