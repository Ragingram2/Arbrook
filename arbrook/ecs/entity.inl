#include "ecs/entity.hpp"
#pragma once

namespace rythe::core::ecs
{
	template<typename componentType>
	inline R_ALWAYS_INLINE componentType& entity::addComponent()
	{
		return *Registry::createComponent<componentType>(m_id);
	}

	//template<typename componentType>
	//inline R_ALWAYS_INLINE componentType& entity::addComponent(const componentType& val)
	//{
	//	auto id = rsl::typeHash<componentType>();
	//	component<componentType>* comp = reinterpret_cast<component<componentType>*>(m_components.emplace(id, std::make_unique<component<componentType>>(val)).first->second.get());
	//	comp->owner = *this;
	//	return *reinterpret_cast<componentType*>(comp);
	//}

	//template<typename componentType>
	//inline R_ALWAYS_INLINE componentType& entity::getComponent()
	//{
	//	auto id = rsl::typeHash<componentType>();
	//	log::debug(m_components[rsl::typeHash<componentType>()].get()->typeId);
	//	component<componentType>* comp = reinterpret_cast<component<componentType>*>(m_components[rsl::typeHash<componentType>()].get());
	//	return *reinterpret_cast<componentType*>(comp);
	//}

	//template<typename componentType>
	//inline R_ALWAYS_INLINE bool entity::hasComponent()
	//{
	//	return m_components.contains(rsl::typeHash<componentType>());
	//}

	//template<typename componentType>
	//inline R_ALWAYS_INLINE void entity::destroyComponent()
	//{
	//	m_components.erase(rsl::typeHash<componentType>());
	//}
}