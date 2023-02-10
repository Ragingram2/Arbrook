#include "systems/system.hpp"
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
	inline std::unordered_map<rsl::id_type, ecs::entity>& System<componentTypes...>::getFilter()
	{
		return std::unordered_map<rsl::id_type, ecs::entity>();
	}
}
