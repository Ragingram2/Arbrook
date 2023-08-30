#include "core/ecs/filter.hpp"
#pragma once

namespace rythe::core::ecs
{
	template<typename... componentTypes>
	inline entity_set::iterator filter<componentTypes...>::begin() noexcept
	{
		return m_entities.begin();
	}

	template<typename... componentTypes>
	inline entity_set::iterator filter<componentTypes...>::end() noexcept
	{
		return m_entities.end();
	}

	template<typename... componentTypes>
	inline entity_set::reverse_iterator filter<componentTypes...>::rbegin() noexcept
	{
		return m_entities.rbegin();
	}

	template<typename... componentTypes>
	inline entity_set::reverse_iterator filter<componentTypes...>::rend() noexcept
	{
		return m_entities.rend();
	}

	template<typename... ComponentTypes>
	inline rsl::size_type filter<ComponentTypes...>::size() noexcept
	{
		return m_entities.size();
	}

	template<typename... ComponentTypes>
	inline bool filter<ComponentTypes...>::empty() noexcept
	{
		return m_entities.empty();
	}

	template<typename... ComponentTypes>
	inline rsl::size_type filter<ComponentTypes...>::count(entity val)
	{
		auto position = std::find(m_entities.begin(), m_entities.end(), val);
		return position != m_entities.end();
	}

	template<typename... ComponentTypes>
	inline bool filter<ComponentTypes...>::contains(entity val)
	{
		auto position = std::find(m_entities.begin(), m_entities.end(), val);
		return position != m_entities.end();
	}

	template<typename... ComponentTypes>
	inline entity_set::iterator filter<ComponentTypes...>::find(entity val)
	{
		return std::find(m_entities.begin(), m_entities.end(), val);
	}

	template<typename... ComponentTypes>
	inline entity& filter<ComponentTypes...>::at(rsl::size_type index)
	{
		return m_entities.at(index);
	}

	template<typename... ComponentTypes>
	inline entity& filter<ComponentTypes...>::operator[](rsl::size_type index)
	{
		return m_entities.at(index);
	}

	template<typename... componentTypes>
	template<typename componentType>
	inline void filter<componentTypes...>::addEntity(events::component_creation<componentType>& evnt)
	{
		if (!contains(evnt.entity) && containsComp(rsl::make_hash<componentType>()))
			m_entities.push_back(evnt.entity);
	}

	template<typename... componentTypes>
	template<typename componentType>
	inline void filter<componentTypes...>::removeEntity(events::component_destruction<componentType>& evnt)
	{
		auto position = find(evnt.entity);
		if (position != m_entities.end())
			m_entities.erase(position-m_entities.begin());
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

