#include "core/systems/system.hpp"
#pragma once

namespace rythe::core
{
	template<typename... componentTypes>
	ecs::Registry* System<componentTypes...>::registry = 0;

	template<typename... componentTypes>
	inline ecs::entity& System<componentTypes...>::createEntity()
	{
		return registry->createEntity();
	}

	template<typename... componentTypes>
	inline ecs::entity& System<componentTypes...>::createEntity(std::string name)
	{
		return registry->createEntity(name);
	}

	template<typename... componentTypes>
	inline void System<componentTypes...>::destroyEntity(ecs::entity& ent)
	{
		registry->destroyEntity(ent);
	}

	template<typename... componentTypes>
	inline void System<componentTypes...>::destroyEntity(rsl::id_type id)
	{
		registry->destroyEntity(id);
	}
	template<typename... componentTypes>
	template<typename event_type>
	inline void System<componentTypes...>::raiseEvent(event_type& evnt)
	{
		Program::Instance().m_registry->get_service<events::EventBus>()->raiseEvent(evnt);
	}

	template<typename... componentTypes>
	template<typename event_type, void(System<componentTypes...>::* func_type)(event_type&)>
	void System<componentTypes...>::bindEvent()
	{
		Program::Instance().m_registry->get_service<events::EventBus>()->bind<event_type, System<componentTypes...>, void(System<componentTypes...>::*)(event_type&)>(*this);
	}

	template<typename... componentTypes>
	template<typename event_type, typename ownerType, void(ownerType::* func_type)(event_type&)>
	void System<componentTypes...>::setKeyBind()
	{
		Program::Instance().m_registry->get_service<events::EventBus>()->bind<event_type, ownerType, void(ownerType::*)(event_type&)>(this*);
	}
}
