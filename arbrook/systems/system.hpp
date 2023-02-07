#pragma once
#include "platform/platform.hpp"
#include "ecs/registry.hpp"
#include "engine/program.hpp"

namespace rythe::core
{
	struct exampleComp : public ecs::component<exampleComp>
	{
		int i = 10;
	};

	template<typename... componentTypes>
	class System
	{
	public:
		static ecs::Registry* registry;
		System()
		{
			registry = Program::Instance().m_registry->get_service<ecs::Registry>();
		}

		virtual ~System() = default;

		virtual void setup() RYTHE_PURE;
		virtual void update() RYTHE_PURE;
		virtual void shutdown() RYTHE_PURE;

		ecs::entity& createEntity();
		ecs::entity& createEntity(std::string name);
		void destroyEntity(ecs::entity& ent);
		void destroyEntity(rsl::id_type id);
	};
}

#include "systems/system.inl"
