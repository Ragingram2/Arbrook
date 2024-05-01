#include "core/ecs/registry.hpp"
#pragma once

namespace rythe::core::ecs
{
	template<typename componentType>
	inline void Registry::registerComponent()
	{
		static rsl::id_type typeId = rsl::typeHash<componentType>();
		if (!componentFamilies.contains(typeId))
		{
			componentFamilies.emplace(typeId, std::make_unique<component_family<componentType>>());
			auto typeName = std::string(rsl::type_name<componentType>());
			size_t pos = 0;
			while ((pos = typeName.find("::")) != std::string::npos) {
				typeName.erase(0, pos + 2);
			}
			componentNames.emplace(typeId, typeName);
			getFamily<componentType>().reserve(100);
		}
	}

	template<typename componentType>
	inline component_family<componentType>& Registry::getFamily()
	{
		static rsl::id_type typeId = rsl::typeHash<componentType>();
		return *reinterpret_cast<component_family<componentType>*>(componentFamilies[typeId].get());
	}

	template<typename componentType>
	inline componentType& Registry::createComponent(ecs::entity& ent)
	{
		//static rsl::id_type typeId = rsl::typeHash<componentType>();

		////Register component with the registry
		//if (!componentFamilies.contains(typeId))
		//{
		//	ecs::Registry::registerComponent<componentType>();
		//}

		////Register component with the entity
		//if (!entityCompositions.contains(ent.m_id))
		//	entityCompositions.emplace(ent.m_id, std::vector<rsl::id_type>());

		//entityCompositions.at(ent.m_id).push_back(typeId);

		return createComponent<componentType>(ent->id);/**reinterpret_cast<componentType*>(getFamily<componentType>().createComponent(ent).ptr)*/;
	}
	template<typename componentType>
	inline componentType& Registry::createComponent(rsl::id_type id)
	{
		static rsl::id_type typeId = rsl::typeHash<componentType>();
		//Register component with the registry
		if (!componentFamilies.contains(typeId))
		{
			ecs::Registry::registerComponent<componentType>();
		}

		//Registry component with the entity
		if (!entityCompositions.contains(id))
			entityCompositions.emplace(id, std::unordered_set<rsl::id_type>());

		entityCompositions.at(id).emplace(typeId);

		return *reinterpret_cast<componentType*>(getFamily<componentType>().createComponent(id).ptr);
	}

	template<typename componentType>
	inline componentType& Registry::createComponent(ecs::entity& ent, componentType&& value)
	{
		//static rsl::id_type typeId = rsl::typeHash<componentType>();

		////Register component with the registry
		//if (!componentFamilies.contains(typeId))
		//{
		//	ecs::Registry::registerComponent<componentType>();
		//}

		////Register component with the entity
		//if (!entityCompositions.contains(ent.m_id))
		//	entityCompositions.emplace(ent.m_id, std::vector<rsl::id_type>());

		//entityCompositions.at(ent.m_id).push_back(typeId);

		return createComponent<componentType>(ent->id, value);/**reinterpret_cast<componentType*>(getFamily<componentType>().createComponent(ent, std::forward<componentType>(value)).ptr)*/;
	}

	template<typename componentType>
	inline componentType& Registry::createComponent(rsl::id_type id, componentType&& value)
	{
		static rsl::id_type typeId = rsl::typeHash<componentType>();
		//Register component with the registry
		if (!componentFamilies.contains(typeId))
		{
			ecs::Registry::registerComponent<componentType>();
		}

		//Registry component with the entity
		if (!entityCompositions.contains(id))
			entityCompositions.emplace(id, std::unordered_set<rsl::id_type>());

		entityCompositions.at(id).emplace(typeId);

		return *reinterpret_cast<componentType*>(getFamily<componentType>().createComponent(id, std::forward<componentType>(value)).ptr);
	}

	template<typename componentType>
	inline componentType& Registry::createComponent(ecs::entity& ent, const componentType& value)
	{
		//static rsl::id_type typeId = rsl::typeHash<componentType>();

		////Register component with the registry
		//if (!componentFamilies.contains(typeId))
		//{
		//	ecs::Registry::registerComponent<componentType>();
		//}

		////Register component with the entity
		//if (!entityCompositions.contains(ent.m_id))
		//	entityCompositions.emplace(ent.m_id, std::vector<rsl::id_type>());

		//entityCompositions.at(ent.m_id).push_back(typeId);

		return createComponent<componentType>(ent->id, value)/**reinterpret_cast<componentType*>(getFamily<componentType>().createComponent(ent, value).ptr)*/;
	}

	template<typename componentType>
	inline componentType& Registry::createComponent(rsl::id_type id, const componentType& value)
	{
		static rsl::id_type typeId = rsl::typeHash<componentType>();
		//Register component with the registry
		if (!componentFamilies.contains(typeId))
		{
			ecs::Registry::registerComponent<componentType>();
		}

		//Registry component with the entity
		if (!entityCompositions.contains(id))
			entityCompositions.emplace(id, std::unordered_set<rsl::id_type>());

		entityCompositions.at(id).emplace(typeId);

		return *reinterpret_cast<componentType*>(getFamily<componentType>().createComponent(id, value).ptr);
	}

	inline void Registry::createComponent(ecs::entity& ent, rsl::id_type compId)
	{
		createComponent(ent->id, compId);
	}

	inline void Registry::createComponent(rsl::id_type id, rsl::id_type compId)
	{
		//Register component with the registry
		if (!componentFamilies.contains(compId))
		{
			log::error("Cannot deduce component type from id");
		}
		log::debug("Creating Component \"{}\"",componentNames[compId]);
		//Registry component with the entity
		if (!entityCompositions.contains(id))
			entityCompositions.emplace(id, std::unordered_set<rsl::id_type>());

		entityCompositions.at(id).emplace(compId);
		componentFamilies[compId].get()->createComponent(id);
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
		//rsl::id_type typeId = rsl::typeHash<componentType>();
		//auto& vec = entityCompositions.at(ent.m_id);
		//auto& position = std::find(vec.begin(), vec.end(), typeId);
		//if (position)
		//	return true;
		return hasComponent<componentType>(ent->id);//false;
	}
	template<typename componentType>
	inline bool Registry::hasComponent(rsl::id_type id)
	{
		rsl::id_type typeId = rsl::typeHash<componentType>();
		auto& vec = entityCompositions.at(id);
		auto position = std::find(vec.begin(), vec.end(), typeId);
		if (position != vec.end())
			return true;
		return false;
	}

	template<typename componentType>
	inline void Registry::destroyComponent(ecs::entity& ent)
	{
		//if (entityCompositions.contains(ent.m_id))
		//{
		//	rsl::id_type typeId = rsl::typeHash<componentType>();
		//	auto& vec = entityCompositions.at(ent.m_id);
		//	auto position = std::find(vec.begin(), vec.end(), typeId);
		//	if (position != vec.end())
		//		vec.erase(position);
		//}

		//auto& family = getFamily<componentType>();
		//family.destroyComponent(ent.m_id);

		destroyComponent<componentType>(ent->id);
	}
	template<typename componentType>
	inline void Registry::destroyComponent(rsl::id_type id)
	{
		if (entityCompositions.contains(id))
		{
			rsl::id_type typeId = rsl::typeHash<componentType>();
			auto& vec = entityCompositions.at(id);
			auto position = std::find(vec.begin(), vec.end(), typeId);
			if (position != vec.end())
				vec.erase(position);
		}

		auto& family = getFamily<componentType>();
		family.destroyComponent(id);
	}
}
