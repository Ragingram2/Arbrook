#include "core/systems/system.hpp"
#pragma once

namespace rythe::core
{
	template<typename SelfType, typename... componentTypes>
	ecs::Registry* System<SelfType, componentTypes...>::registry = 0;

	template<typename SelfType, typename... componentTypes>
	inline ecs::entity System<SelfType, componentTypes...>::createEntity()
	{
		return registry->createEntity();
	}

	template<typename SelfType, typename... componentTypes>
	inline ecs::entity System<SelfType, componentTypes...>::createEntity(std::string name)
	{
		return registry->createEntity(name);
	}

	template<typename SelfType, typename... componentTypes>
	inline void System<SelfType, componentTypes...>::destroyEntity(ecs::entity& ent)
	{
		registry->destroyEntity(ent);
	}

	template<typename SelfType, typename... componentTypes>
	inline void System<SelfType, componentTypes...>::destroyEntity(rsl::id_type id)
	{
		registry->destroyEntity(id);
	}
	template<typename SelfType, typename... componentTypes>
	template<typename event_type>
	inline void System<SelfType, componentTypes...>::raiseEvent(event_type&& evnt)
	{
		events::EventBus::raiseEvent(evnt);
	}

	template<typename SelfType, typename... componentTypes>
	template<typename event_type, void(SelfType::* func_type)(event_type&)>
	void System<SelfType, componentTypes...>::bindEvent()
	{
		events::EventBus::bind<event_type, SelfType, func_type>(*static_cast<SelfType*>(this));
	}

	//template<typename... componentTypes>
	//template<typename event_type, typename ownerType, void(ownerType::* func_type)(event_type&)>
	//void System<componentTypes...>::setKeyBind()
	//{
	//	Program::Instance().m_registry->get_service<events::EventBus>()->bind<event_type, ownerType, void(ownerType::*)(event_type&)>(this*);
	//}
}
