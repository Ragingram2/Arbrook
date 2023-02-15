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
			getFamily<componentType>().reserve(100);
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
		if (!m_entityCompositions.contains(ent.m_id))
			m_entityCompositions.emplace(ent.m_id, std::vector<rsl::id_type>());

		m_entityCompositions.at(ent.m_id).push_back(typeId);

		return *reinterpret_cast<componentType*>(getFamily<componentType>().createComponent(ent).ptr);
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
		if (!m_entityCompositions.contains(id))
			m_entityCompositions.emplace(id, std::vector<rsl::id_type>());

		m_entityCompositions.at(id).push_back(typeId);

		return *reinterpret_cast<componentType*>(getFamily<componentType>().createComponent(id).ptr);
	}

	template<typename componentType>
	inline componentType& Registry::getComponent(ecs::entity& ent)
	{
		return *reinterpret_cast<componentType*>(getFamily<componentType>().getComponent(ent).ptr);
	}
	template<typename componentType>
	inline componentType& Registry::getComponent(rsl::id_type id)
	{
		return *reinterpret_cast<componentType*>(getFamily<componentType>().getComponent(id).ptr);
	}

	template<typename componentType>
	inline bool Registry::hasComponent(ecs::entity& ent)
	{
		rsl::id_type typeId = rsl::typeHash<componentType>();
		auto& vec = m_entityCompositions.at(ent.m_id);
		auto& position = std::find(vec.begin(), vec.end(), typeId);
		if (position)
			return true;
		return false;
	}
	template<typename componentType>
	inline bool Registry::hasComponent(rsl::id_type id)
	{
		rsl::id_type typeId = rsl::typeHash<componentType>();
		auto& vec = m_entityCompositions.at(id);
		auto position = std::find(vec.begin(), vec.end(), typeId);
		if (position != vec.end())
			return true;
		return false;
	}

	template<typename componentType>
	inline void Registry::destroyComponent(ecs::entity& ent)
	{
		if (m_entityCompositions.contains(ent.m_id))
		{
			rsl::id_type typeId = rsl::typeHash<componentType>();
			auto& vec = m_entityCompositions.at(ent.m_id);
			auto position = std::find(vec.begin(), vec.end(), typeId);
			if (position != vec.end())
				vec.erase(position);
		}

		auto& family = getFamily<componentType>();
		family.destroyComponent(ent.m_id);
	}
	template<typename componentType>
	inline void Registry::destroyComponent(rsl::id_type id)
	{
		if (m_entityCompositions.contains(id))
		{
			rsl::id_type typeId = rsl::typeHash<componentType>();
			auto& vec = m_entityCompositions.at(id);
			auto position = std::find(vec.begin(), vec.end(), typeId);
			if (position != vec.end())
				vec.erase(position);
		}

		auto& family = getFamily<componentType>();
		family.destroyComponent(id);
	}
}
