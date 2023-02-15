#include "ecs/filter.hpp"
#pragma once

namespace rythe::core::ecs
{
	template<typename... componentTypes>
	template<typename componentType>
	inline void filter<componentTypes...>::addEntity(events::component_creation<componentType>& evnt)
	{
		//log::debug(typeid(componentType).name());
		m_entities.emplace(evnt.entity.m_id,evnt.entity);
	}

	template<typename... componentTypes>
	template<typename componentType>
	inline void filter<componentTypes...>::removeEntity(events::component_destruction<componentType>& evnt)
	{
		//log::debug(typeid(componentType).name());
		//m_entities.erase(std::remove(m_entities.begin(), m_entities.end(), evnt.entity), m_entities.end());
		m_entities.erase(evnt.entity.m_id);
	}

	//template<typename... componentTypes>
	//template<typename componentType>
	//R_NODISCARD inline component_container<componentType>& filter<componentTypes...>::get()
	//{
	//	auto& container = std::get<component_container<componentType>>(m_containers);
	//	container.clear();
	//	ecs::Registry::getFamily<componentType>().fillContainer(container);
	//	return container;
	//}
}

