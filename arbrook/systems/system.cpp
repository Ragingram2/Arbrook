#include "systems/system.hpp"

namespace rythe::core
{
	ecs::Registry* System::registry = Program::Instance().m_registry->get_service<ecs::Registry>();

	void System::setup()
	{

	}

	ecs::entity System::createEntity()
	{
		System::registry->createEntity();
	}

	ecs::entity System::createEntity(std::string name)
	{
		System::registry->createEntity(name);
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