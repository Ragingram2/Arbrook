#include "ecs/registry.hpp"

namespace rythe::core::ecs
{
	std::unordered_map<rsl::id_type, ecs::entity> Registry::m_entities;

	ecs::entity& Registry::createEntity()
	{
		m_entities.emplace(m_lastId++,ecs::entity(m_lastId));
	}

	ecs::entity& Registry::createEntity(const std::string& name)
	{
		m_entities.emplace(m_lastId++,ecs::entity(m_lastId, name));
	}

	void Registry::destroyEntity(ecs::entity& ent)
	{
		m_entities.erase(ent.m_id);
	}

	void Registry::destroyEntity(rsl::id_type id)
	{
		m_entities.erase(id);
	}
}