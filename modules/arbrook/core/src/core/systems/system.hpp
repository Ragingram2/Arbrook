#pragma once
#include <rsl/primitives>

#include "core/ecs/registry.hpp"
#include "core/engine/program.hpp"
#include "core/ecs/component_container.hpp"
#include "core/ecs/filter.hpp"

namespace rythe::core
{
	class SystemBase
	{
	public:
		virtual ~SystemBase() = default;
	};

	template<typename SelfType, typename... componentTypes>
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
		ecs::entity createEntity();
		ecs::entity createEntity(std::string name);
		void destroyEntity(ecs::entity& ent);
		void destroyEntity(rsl::id_type id);

		template<typename event_type>
		void raiseEvent(event_type&& evnt);

		template<typename event_type, void(SelfType::* func_type)(event_type&)>
		void bindEvent();

		//template<typename event_type,  typename ownerType = System<componentTypes...>, void(ownerType::* func_type)(event_type&)>
		//void setKeyBind();
	};
}

#include "core/systems/system.inl"
