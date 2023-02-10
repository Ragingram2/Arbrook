#include "ecs/component_family.hpp"
#pragma once

namespace rythe::core::ecs
{
	using entityId = rsl::id_type;

	template<typename componentType>
	inline void component_family<componentType>::reserve(rsl::size_type size)
	{
		m_components.reserve(size);
	}

	template<typename componentType>
	inline void component_family<componentType>::clear()
	{
		m_components.clear();
	}

	template<typename componentType>
	inline pointer<void> component_family<componentType>::createComponent(entityId id)
	{
		m_components.try_emplace(id);
		return { &m_components.at(id) };
	}

	template<typename componentType>
	inline pointer<void> component_family<componentType>::createComponent(entity& ent)
	{
		m_components.try_emplace(ent.m_id);
		return { &m_components.at(ent.m_id) };
	}

	template<typename componentType>
	inline pointer<void> component_family<componentType>::getComponent(entity& ent)
	{
		return { &m_components.at(ent.m_id) };
	}

	template<typename componentType>
	inline pointer<void> component_family<componentType>::getComponent(entityId id)
	{
		return { &m_components.at(id) };
	}

	template<typename componentType>
	inline void component_family<componentType>::destroyComponent(entity& ent)
	{
		m_components.erase(ent.m_id);
	}

	template<typename componentType>
	inline void component_family<componentType>::destroyComponent(entityId id)
	{
		m_components.erase(id);
	}
}
