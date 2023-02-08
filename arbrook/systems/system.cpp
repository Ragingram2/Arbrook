#include "systems/system.hpp"

namespace rythe::core
{
	template<typename... componentTypes>
	ecs::Registry* System<componentTypes...>::registry;

	template<typename... componentTypes>
	ecs::entity& System<componentTypes...>::createEntity()
	{
		return System<componentTypes...>::registry->createEntity();
	}

	template<typename... componentTypes>
	ecs::entity& System<componentTypes...>::createEntity(std::string name)
	{
		return System<componentTypes...>::registry->createEntity(name);
	}

	template<typename... componentTypes>
	void System<componentTypes...>::destroyEntity(ecs::entity& ent)
	{
		System<componentTypes...>::destroyEntity(ent);
	}

	template<typename... componentTypes>
	void System<componentTypes...>::destroyEntity(rsl::id_type id)
	{
		System<componentTypes...>::destroyEntity(id);
	}

	template<typename... componentTypes>
	std::unordered_map<rsl::id_type, ecs::entity>& System<componentTypes...>::getFilter()
	{
		return std::unordered_map<rsl::id_type, ecs::entity>();
	}
}