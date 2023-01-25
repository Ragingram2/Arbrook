#include "ecs/registry.hpp"
#pragma once

namespace rythe::core::ecs
{
	template<typename componentType>
	inline pointer<componentType> Registry::getComponent(ecs::entity& ent)
	{
		return m_componentPools[typeHash<componentType>()].getComponent<componentType>(ent);
	}
	template<typename componentType>
	inline pointer<componentType> Registry::getComponent(rsl::id_type id)
	{
		return m_componentPools[typeHash<componentType>()].getComponent<componentType>(id);
	}
	template<typename componentType>
	inline bool Registry::hasComponent(ecs::entity& ent)
	{
		return false;
	}
	template<typename componentType>
	inline bool Registry::hasComponent(rsl::id_type id)
	{
		return false;
	}
	template<typename componentType>
	inline void Registry::destroyComponent(ecs::entity& ent)
	{
	}
	template<typename componentType>
	inline void Registry::destroyComponent(rsl::id_type id)
	{
	}
}
