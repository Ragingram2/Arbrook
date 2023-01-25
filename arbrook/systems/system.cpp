#include "systems/system.hpp"

namespace rythe::core
{
	ecs::Registry* System::registry;

	ecs::entity& System::createEntity()
	{
		return System::registry->createEntity();
	}

	ecs::entity& System::createEntity(std::string name)
	{
		return System::registry->createEntity(name);
	}

	void System::destroyEntity(ecs::entity& ent)
	{
		System::destroyEntity(ent);
	}

	void System::destroyEntity(rsl::id_type id)
	{
		System::destroyEntity(id);
	}
}