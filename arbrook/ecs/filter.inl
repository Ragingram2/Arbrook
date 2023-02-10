#include "ecs/filter.hpp"
#pragma once

namespace rythe::core::ecs
{
	template<typename... componentTypes>
	template<typename componentType>
	R_NODISCARD inline component_container<componentType>& filter<componentTypes...>::get()
	{
		auto& container = std::get<component_container<componentType>>(m_containers);
		container.clear();
		ecs::Registry::getFamily<componentType>().fillContainer(container);
		return container;
	}
}

