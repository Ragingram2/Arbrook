#include "ecs/entity.hpp"
#pragma once

namespace rythe::core::ecs
{
	template<typename componentType>
	inline R_ALWAYS_INLINE componentType& entity::addComponent()
	{
		return *reinterpret_cast<componentType*>(reinterpret_cast<component<componentType>*>(m_components.emplace(rsl::typeHash<componentType>(), std::make_unique<component<componentType>>()).first->second.get()));
	}

	template<typename componentType>
	inline R_ALWAYS_INLINE componentType& entity::addComponent(const componentType& val)
	{
		return *reinterpret_cast<componentType*>(reinterpret_cast<component<componentType>*>(m_components.emplace(rsl::typeHash<componentType>(), std::make_unique<component<componentType>>(val)).first->second.get()));
	}

	template<typename componentType>
	inline R_ALWAYS_INLINE componentType& entity::getComponent()
	{
		return *reinterpret_cast<componentType*>(reinterpret_cast<component<componentType>*>(m_components[rsl::typeHash<componentType>()].get()));
	}

	template<typename componentType>
	inline R_ALWAYS_INLINE bool entity::hasComponent()
	{
		return m_components.contains(rsl::typeHash<componentType>());
	}

	template<typename componentType>
	inline R_ALWAYS_INLINE void entity::destroyComponent()
	{
		m_components.erase(rsl::typeHash<componentType>());
	}
}