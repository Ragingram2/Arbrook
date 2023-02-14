#pragma once
#include "platform/platform.hpp"
#include "ecs/registry.hpp"
#include "engine/program.hpp"
#include "ecs/component_container.hpp"
#include "ecs/filter.hpp"

namespace rythe::core
{
	struct exampleComp /*: public ecs::component<exampleComp>*/
	{
		int i = 10;
	};

	struct exampleComp2 /*: public ecs::component<exampleComp>*/
	{
		int b = 69;
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
		ecs::filter<componentTypes...> m_filter;
		System()
		{
			registry = Program::Instance().m_registry->get_service<ecs::Registry>();
		}

		virtual ~System() = default;
	public:

		virtual void setup() RYTHE_PURE;
		virtual void update() RYTHE_PURE;
		virtual void shutdown() RYTHE_PURE;

		ecs::entity& createEntity();
		ecs::entity& createEntity(std::string name);
		void destroyEntity(ecs::entity& ent);
		void destroyEntity(rsl::id_type id);

		//std::unordered_map<rsl::id_type, ecs::entity>& getFilter();
	};
}

#include "systems/system.inl"
