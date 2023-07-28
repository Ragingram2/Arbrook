#pragma once
#include <rsl/primitives>

#include "core/ecs/registry.hpp"
#include "core/engine/program.hpp"
#include "core/ecs/component_container.hpp"
#include "core/ecs/filter.hpp"

namespace rythe::core
{
	struct exampleComp
	{
		float time = 10;
		float inc = 0.001;
	};

	struct exampleComp2
	{
		int b = 69;
	};

	struct transform
	{
		math::vec3 position = math::vec3(0.0f, 0.0f,0.0f);
		math::vec2 scale = math::vec2(1.0f, 1.0f);
		float rotation = 0;
	};

	struct rigidbody
	{
		math::vec2 prevVelocity = math::vec2(0.f, 0.f);
		math::vec2 velocity = math::vec2(0.f, 0.f);
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

		//virtual void setup() RYTHE_PURE;
		//virtual void update() RYTHE_PURE;
		//virtual void shutdown() RYTHE_PURE;

		ecs::entity& createEntity();
		ecs::entity& createEntity(std::string name);
		void destroyEntity(ecs::entity& ent);
		void destroyEntity(rsl::id_type id);

		template<typename event_type>
		void raiseEvent(event_type& evnt);

		template<typename event_type, void(System<componentTypes...>::* func_type)(event_type&)>
		void bindEvent();

		//template<typename event_type,  typename ownerType = System<componentTypes...>, void(ownerType::* func_type)(event_type&)>
		//void setKeyBind();
	};
}

#include "core/systems/system.inl"
