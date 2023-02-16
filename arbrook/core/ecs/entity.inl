#include "core/ecs/entity.hpp"
#pragma once

namespace rythe::core::ecs
{
	template<typename componentType>
	inline componentType& entity::addComponent()
	{
		return Registry::createComponent<componentType>(m_id);
	}

	template<typename componentType>
	inline componentType& entity::getComponent()
	{
		return Registry::getComponent<componentType>(m_id);
	}

	template<typename componentType>
	inline bool entity::hasComponent()
	{
		return Registry::hasComponent<componentType>(m_id);
	}

	template<typename componentType>
	inline void entity::destroyComponent()
	{
		return Registry::destroyComponent<componentType>(m_id);
	}
}