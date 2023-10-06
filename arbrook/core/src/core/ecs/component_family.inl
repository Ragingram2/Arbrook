#include "core/ecs/component_family.hpp"
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
		events::component_creation<componentType> compCreate{ id };
		events::EventBus::raiseEvent<events::component_creation<componentType>>(compCreate);

		m_components.try_emplace(id);

		//if constexpr (has_m_owner<componentType>)
		//{
		//	log::debug("Setting Owner to Entity with ID {}",id);
		//	m_components.at(id).m_owner = ecs::entity{ &Registry::entities[id] };
		//}
		//else
		//{
		//	log::debug("Component does not have member");
		//}
		return { &m_components.at(id) };
	}

	template<typename componentType>
	inline pointer<void> component_family<componentType>::createComponent(entity& ent)
	{
		events::component_creation<componentType> compCreate{ ent->id };
		events::EventBus::raiseEvent<events::component_creation<componentType>>(compCreate);

		m_components.try_emplace(ent->id);

		//if constexpr (has_m_owner<componentType>)
		//{
		//	log::debug("Setting Owner to Entity with ID {}", ent->id);
		//	m_components.at(ent->id).m_owner = ent;
		//}
		//else
		//{
		//	log::debug("Component does not have member");
		//}
		return { &m_components.at(ent->id) };
	}

	template<typename componentType>
	inline pointer<void> component_family<componentType>::getComponent(entity& ent)
	{
		return { &m_components.at(ent->id) };
	}

	template<typename componentType>
	inline pointer<void> component_family<componentType>::getComponent(entityId id)
	{
		return { &m_components.at(id) };
	}

	template<typename componentType>
	inline void component_family<componentType>::destroyComponent(entity& ent)
	{
		events::component_destruction<componentType> compDestruct{ ent->id };
		events::EventBus::raiseEvent<events::component_destruction<componentType>>(compDestruct);

		m_components.erase(ent->id);
	}

	template<typename componentType>
	inline void component_family<componentType>::destroyComponent(entityId id)
	{
		events::component_destruction<componentType> compDestruct{ id };
		events::EventBus::raiseEvent<events::component_destruction<componentType>>(compDestruct);

		m_components.erase(id);
	}

	//template<typename componentType>
	//inline void component_family<componentType>::fillContainer(component_container<componentType>& container, std::vector<entity> entities)
	//{
	//	container.reserve(entities.size());

	//	for (auto ent : entities)
	//		container.emplace_back(m_components.at(ent.m_id));
	//}
}
