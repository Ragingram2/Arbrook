#include "ecs/registry.hpp"
#pragma once

namespace rythe::core::ecs
{
	template<typename componentType>
	inline void Registry::registerComponent()
	{
		static rsl::id_type typeId = rsl::typeHash<componentType>();
		if (!m_componentFamilies.contains(typeId))
		{
			m_componentFamilies.emplace(typeId, std::make_unique<component_family<componentType>>());
		}
	}

	template<typename componentType>
	inline component_family<componentType>& Registry::getFamily()
	{
		static rsl::id_type typeId = rsl::typeHash<componentType>();
		return *reinterpret_cast<component_family<componentType>*>(m_componentFamilies[typeId].get());
	}

	template<typename componentType>
	inline componentType& Registry::createComponent(ecs::entity& ent)
	{
		static rsl::id_type typeId = rsl::typeHash<componentType>();

		//Register component with the registry
		if (!m_componentFamilies.contains(typeId))
		{
			ecs::Registry::registerComponent<componentType>();
		}

		//Register component with the entity
		if (m_entityCompositions.contains(ent.m_id))
		{
			m_entityCompositions.at(ent.m_id).push_back(typeId);
		}//otherwise maybe error?

		auto& family = getFamily<componentType>();
		return family.createComponent(ent);
	}
	template<typename componentType>
	inline componentType& Registry::createComponent(rsl::id_type id)
	{
		static rsl::id_type typeId = rsl::typeHash<componentType>();
		//Register component with the registry
		if (!m_componentFamilies.contains(typeId))
		{
			ecs::Registry::registerComponent<componentType>();
		}

		//Registry component with the entity
		if (m_entityCompositions.contains(id))
		{
			m_entityCompositions.at(id).push_back(typeId);
		}//otherwise maybe error?

		auto& family = getFamily<componentType>();
		return family.createComponent(id);
	}

	template<typename componentType>
	inline componentType& Registry::getComponent(ecs::entity& ent)
	{
		return getFamily<componentType>().getComponent<componentType>(ent);
	}
	template<typename componentType>
	inline componentType& Registry::getComponent(rsl::id_type id)
	{
		return getFamily<componentType>().getComponent<componentType>(id);
	}

	template<typename componentType>
	inline bool Registry::hasComponent(ecs::entity& ent)
	{
		rsl::id_type typeId = rsl::typeHash<componentType>();
		return m_entityCompositions.at(ent.m_id).contains(typeId);
	}
	template<typename componentType>
	inline bool Registry::hasComponent(rsl::id_type id)
	{
		rsl::id_type typeId = rsl::typeHash<componentType>();
		return m_entityCompositions.at(id).contains(typeId);
	}

	template<typename componentType>
	inline void Registry::destroyComponent(ecs::entity& ent)
	{
		if (m_entityCompositions.contains(ent.m_id))
		{
			if (m_entityCompositions.at(ent.m_id))
			{
				rsl::id_type typeId = rsl::typeHash<componentType>();
				m_entityCompositions.at(ent.m_id).erase(typeId);
			}
		}

		auto& family = getFamily<componentType>();
		family.destroyComponent<componentType>(ent.m_id);
	}
	template<typename componentType>
	inline void Registry::destroyComponent(rsl::id_type id)
	{
		if (m_entityCompositions.contains(id))
		{
			if (m_entityCompositions.at(ent.m_id))
			{
				rsl::id_type typeId = rsl::typeHash<componentType>();
				m_entityCompositions.at(ent.m_id).erase(typeId);
			}
		}

		auto& family = getFamily<componentType>();
		family.destroyComponent<componentType>(id);
	}
}
