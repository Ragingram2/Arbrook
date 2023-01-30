#include "ecs/registry.hpp"

namespace rythe::core::ecs
{
	using entityId = rsl::id_type;
	using componentId = rsl::id_type;

	std::unordered_map<entityId, ecs::entity> Registry::m_entities;
	std::unordered_map<entityId, std::vector<rsl::id_type>> Registry::m_entityCompositions;
	std::unordered_map<componentId, std::unique_ptr<component_family_base>> Registry::m_componentFamilies;

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