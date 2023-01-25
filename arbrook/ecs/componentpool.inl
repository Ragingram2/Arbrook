#include "ecs/componentpool.hpp"
#pragma once


namespace rythe::core::ecs
{
	template<typename componentType>
	inline void component_pool<componentType>::reserve(rsl::size_type amount)
	{
		m_components.reserve(amount);
	}

	template<typename componentType>
	inline void component_pool<componentType>::clear()
	{
		m_components.clear();
	}

	template<typename componentType>
	inline R_NODISCARD bool component_pool<componentType>::contains(entity target) const
	{
		return m_components.contains(target.m_id);
	}

	template<typename componentType>
	inline pointer<component_base> component_pool<componentType>::create_component(entity target)
	{
		return m_components.emplace(target.m_id);
	}

	template<typename componentType>
	inline R_NODISCARD pointer<component_base> component_pool<componentType>::get_component(entity target)
	{
		return m_components[target.m_id];
	}

	template<typename componentType>
	inline R_NODISCARD const pointer<component_base> component_pool<componentType>::get_component(entity target) const
	{
		return m_components[target.m_id];
	}

	template<typename componentType>
	inline void component_pool<componentType>::destroy_component(entity target)
	{
		m_components.erase(target.m_id);
	}
}