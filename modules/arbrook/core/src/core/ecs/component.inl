#include "core/ecs/component.hpp"
#pragma once

namespace rythe::core::ecs
{
    template<typename componentType>
    inline component<componentType>& component<componentType>::operator=(const componentType& src)
    {
        owner.getComponent<componentType>() = src;
        return *this;
    }

    template<typename componentType>
    inline component<componentType>& component<componentType>::operator=(componentType&& src)
    {
        owner.getComponent<componentType>() = std::move(src);
        return *this;
    }

    template<typename componentType>
    inline component<componentType>::operator componentType& ()
    {
        return owner.getComponent<componentType>();
    }

    template<typename componentType>
    inline component<componentType>::operator const componentType& () const
    {
        return owner.getComponent<componentType>();
    }

    template<typename componentType>
    inline bool component<componentType>::valid() const noexcept
    {
        return owner.hasComponent<componentType>();
    }

    template<typename componentType>
    inline component<componentType>::operator bool() const noexcept
    {
        return owner.hasComponent<componentType>();
    }

    template<typename componentType>
    [[nodiscard]] componentType& component<componentType>::operator*()
    {
        return owner.getComponent<componentType>();
    }

    template<typename componentType>
    [[nodiscard]] const componentType& component<componentType>::operator*() const
    {
        return owner.getComponent<componentType>();
    }

    template<typename componentType>
    inline pointer<componentType> component<componentType>::operator->()
    {
        return &owner.getComponent<componentType>();
    }

    template<typename componentType>
    inline const pointer<componentType> component<componentType>::operator->() const
    {
        return &owner.getComponent<componentType>();
    }

    template<typename componentType>
    inline bool component<componentType>::operator==(const component& other) const noexcept
    {
        return owner == other.owner;
    }

    template<typename componentType>
    inline componentType& component<componentType>::get()
    {
        return owner.getComponent<componentType>();
    }

    template<typename componentType>
    inline const componentType& component<componentType>::get() const
    {
        return owner.getComponent<componentType>();
    }

    template<typename componentType>
    inline void component<componentType>::destroy()
    {
        owner.destroyComponent<componentType>();
    }
}
