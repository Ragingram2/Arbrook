#include "ecs/registry.hpp"

namespace rythe::core::ecs
{
	std::unordered_map<rsl::id_type, ecs::entity> Registry::m_entities;
	std::unordered_map<rsl::id_type, std::unique_ptr<component_pool_base>>  Registry::m_componentPools;

	ecs::entity& Registry::createEntity()
	{
		m_lastId++;
		m_entities.try_emplace(m_lastId, ecs::entity{ m_lastId });
		return m_entities.at(m_lastId);
	}

	ecs::entity& Registry::createEntity(const std::string& name)
	{
		m_lastId++;
		m_entities.try_emplace(m_lastId, ecs::entity{ m_lastId, name });
		return m_entities.at(m_lastId);
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