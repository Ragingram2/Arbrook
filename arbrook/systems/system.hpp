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

	class SystemBase
	{
	public:
		virtual ~SystemBase() = default;
	};

	template<typename... componentTypes>
	class System : public SystemBase
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

		inline ecs::entity& createEntity();
		inline ecs::entity& createEntity(std::string name);
		inline void destroyEntity(ecs::entity& ent);
		inline void destroyEntity(rsl::id_type id);

		inline std::unordered_map<rsl::id_type, ecs::entity>& getFilter();
	};
}

#include "systems/system.inl"
