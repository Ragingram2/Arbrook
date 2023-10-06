#include "core/ecs/entity.hpp"
#include "core/ecs/entity_data.hpp"
#pragma once

namespace std
{
    inline rythe_always_inline size_t hash<rythe::core::ecs::entity>::operator()(rythe::core::ecs::entity const& handle) const noexcept
    {
        return handle.data != nullptr ? handle->id : invalid_id;
    }
}

namespace rythe::core::ecs
{

	template<typename componentType>
	inline componentType& entity::addComponent()
	{
		return Registry::createComponent<componentType>(data->id);
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

    template<>
    inline rythe_always_inline bool entity::operator==<std::nullptr_t>(std::nullptr_t) const
    {
        return !(data && data->alive);
    }

    template<>
    inline rythe_always_inline bool entity::operator!=<std::nullptr_t>(std::nullptr_t) const
    {
        return data && data->alive;
    }

    template<>
    inline rythe_always_inline bool entity::operator==<rsl::id_type>(rsl::id_type id) const
    {
        return data && data->alive ? data->id == id : id == invalid_id;
    }

    template<>
    inline rythe_always_inline bool entity::operator!=<rsl::id_type>(rsl::id_type id) const
    {
        return data && data->alive && (data->id != id || id == invalid_id);
    }

    template<>
    inline rythe_always_inline bool entity::operator==<entity>(entity other) const
    {
        return data && data->alive && other && data->id == other->id;
    }

    template<>
    inline rythe_always_inline bool entity::operator!=<entity>(entity other) const
    {
        return data && data->alive && other && data->id != other->id;
    }

    template<>
    inline rythe_always_inline bool entity::operator==<entity_data>(entity_data other) const
    {
        return data && data->alive && data->id == other.id;
    }

    template<>
    inline rythe_always_inline bool entity::operator!=<entity_data>(entity_data other) const
    {
        return data && data->alive && data->id != other.id;
    }

    template<typename T>
    inline rythe_always_inline bool entity::operator==(T val) const
    {
        return data && data->alive ? data->id == val : val == invalid_id;
    }

    template<typename T>
    inline rythe_always_inline bool entity::operator!=(T val) const
    {
        return data && data->alive && (data->id != val || val == invalid_id);
    }
}