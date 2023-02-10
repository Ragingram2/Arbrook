#include "ecs/component_family_base.hpp"

namespace rythe::core::ecs
{
	std::any& component_family_base::createComponent(entity& ent)
	{
		m_componentData.emplace(ent.m_id, std::make_any<void*>());
		//m_componentData.emplace(ent.m_id);
		return m_componentData[ent.m_id];
	}

	std::any& component_family_base::createComponent(entityId id)
	{
		m_componentData.emplace(id, std::make_any<void*>());
		//m_componentData.emplace(id);
		return m_componentData[id];
	}

	std::any& component_family_base::getComponent(entity& ent)
	{
		return m_componentData[ent.m_id];
	}

	std::any& component_family_base::getComponent(entityId id)
	{
		return m_componentData[id];
	}

	void component_family_base::destroyComponent(entityId id)
	{
		m_componentData.erase(id);
	}
}