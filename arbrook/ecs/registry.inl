#include "ecs/registry.hpp"
#pragma once

namespace rythe::core::ecs
{
	template<typename componentType>
	inline void Registry::registerComponent()
	{
		m_componentFamilies.emplace(rsl::typeHash<componentType>(), std::make_unique<component_family<componentType>>());
	}

	template<typename componentType>
	inline component_family<componentType>& Registry::getFamily()
	{
		return *reinterpret_cast<component_family<componentType>*>(m_componentFamilies[rsl::typeHash<componentType>()].get());
	}

	//template<typename componentType>
	//inline pointer<componentType> Registry::createComponent(ecs::entity& ent)
	//{
	//	//Registry component with the entity
	//	m_entityCompositions.at(ent.m_id).push_back(rsl::typeHash<componentType>());

	//	return m_componentPools[typeHash<componentType>()].getComponent<componentType>(ent);
	//}
	//template<typename componentType>
	//inline pointer<componentType> Registry::createComponent(rsl::id_type id)
	//{
	//	//Registry component with the entity
	//	m_entityCompositions.at(ent.m_id).push_back(rsl::typeHash<componentType>());

	//	return m_componentPools[].getComponent<componentType>(id);
	//}

	//template<typename componentType>
	//inline pointer<componentType> Registry::getComponent(ecs::entity& ent)
	//{
	//	return m_componentPools[typeHash<componentType>()].getComponent<componentType>(ent);
	//}
	//template<typename componentType>
	//inline pointer<componentType> Registry::getComponent(rsl::id_type id)
	//{
	//	return m_componentPools[typeHash<componentType>()].getComponent<componentType>(id);
	//}

	//template<typename componentType>
	//inline bool Registry::hasComponent(ecs::entity& ent)
	//{
	//	return false;
	//}
	//template<typename componentType>
	//inline bool Registry::hasComponent(rsl::id_type id)
	//{
	//	return false;
	//}
	//template<typename componentType>
	//inline void Registry::destroyComponent(ecs::entity& ent)
	//{
	//}
	//template<typename componentType>
	//inline void Registry::destroyComponent(rsl::id_type id)
	//{
	//}
}
