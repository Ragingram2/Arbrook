#include "entity.hpp"
#include "registry.hpp"
#pragma once


namespace rythe::core::ecs
{

	template<typename componentType>
	inline componentType& entity::addComponent()
	{
		return Registry::createComponent<componentType>(data->id);
	}

	template<typename componentType>
	inline componentType& entity::addComponent(const componentType& value)
	{
		return Registry::createComponent<componentType>(data->id, value);
	}

	template<typename componentType>
	inline componentType& entity::addComponent(componentType&& value)
	{
		return Registry::createComponent<componentType>(data->id, std::forward<componentType>(value));
	}

	template<typename componentType>
	inline componentType& entity::getComponent()
	{
		return Registry::getComponent<componentType>(data->id);
	}

	template<typename componentType>
	inline bool entity::hasComponent()
	{
		return Registry::hasComponent<componentType>(data->id);
	}

	template<typename componentType>
	inline void entity::destroyComponent()
	{
		return Registry::destroyComponent<componentType>(data->id);
	}
}