#include "ecs/component_family.hpp"
#pragma once

namespace rythe::core::ecs
{
	template<typename componentType>
	inline componentType& component_family<componentType>::createComponent(entity& ent)
	{
		m_componentData.emplace(ent.m_id, std::make_any<void*>());
		//m_componentData.emplace(m_id);
		return *reinterpret_cast<componentType*>(std::any_cast<void*>(m_componentData[ent.m_id]));
		//return *reinterpret_cast<componentType*>(*m_componentData[ent.m_id]);
		//return *std::any_cast<componentType*>(m_componentData[ent.m_id]);
	}
	template<typename componentType>
	inline componentType& component_family<componentType>::createComponent(entityId id)
	{
		m_componentData.emplace(id, std::make_any<void*>());
		//m_componentData.emplace(id);
		return *reinterpret_cast<componentType*>(std::any_cast<void*>(m_componentData[id]));
		//return *reinterpret_cast<componentType*>(*m_componentData[id]);
		//return *std::any_cast<componentType*>(m_componentData[id]);
	}

	template<typename componentType>
	inline componentType& component_family<componentType>::getComponent(entity& ent)
	{
		if (m_componentData.contains(ent.m_id))
		{
			//return *reinterpret_cast<componentType*>(*m_componentData[ent.m_id]);
			return *std::any_cast<componentType*>(m_componentData[ent.m_id]);
		}

		return { nullptr };
	}
	template<typename componentType>
	inline componentType& component_family<componentType>::getComponent(entityId id)
	{
		if (m_componentData.contains(id))
		{
			//return *reinterpret_cast<componentType*>(*m_componentData[id]);
			return *std::any_cast<componentType*>(m_componentData[ent.id]);
		}

		return { nullptr };
	}

	template<typename componentType>
	inline void component_family<componentType>::destroyComponent(entity& ent)
	{
		m_componentData.erase(ent.m_id);
	}
	template<typename componentType>
	inline void component_family<componentType>::destroyComponent(entityId id)
	{
		m_componentData.erase(id);
	}
}
