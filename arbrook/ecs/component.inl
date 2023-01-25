#include "ecs/component.hpp"
#pragma once

namespace rythe::core::ecs
{
    template<typename componentType>
    inline R_ALWAYS_INLINE component<componentType>& component<componentType>::operator=(const componentType& src)
    {
        Registry::getComponent<componentType>(owner) = src;
        return *this;
    }

    template<typename componentType>
    inline R_ALWAYS_INLINE component<componentType>& component<componentType>::operator=(componentType&& src)
    {
        Registry::getComponent<componentType>(owner) = std::move(src);
        return *this;
    }

    template<typename componentType>
    inline R_ALWAYS_INLINE component<componentType>::operator componentType& ()
    {
        return Registry::getComponent<componentType>(owner);
    }

    template<typename componentType>
    inline R_ALWAYS_INLINE component<componentType>::operator const componentType& () const
    {
        return Registry::getComponent<componentType>(owner);
    }

    template<typename componentType>
    inline R_ALWAYS_INLINE bool component<componentType>::valid() const noexcept
    {
        return Registry::hasComponent<componentType>(owner);
    }

    template<typename componentType>
    inline R_ALWAYS_INLINE component<componentType>::operator bool() const noexcept
    {
        return Registry::hasComponent<componentType>(owner);
    }

    template<typename componentType>
    R_NODISCARD componentType& component<componentType>::operator*()
    {
        return Registry::getComponent<componentType>(owner);
    }

    template<typename componentType>
    R_NODISCARD const componentType& component<componentType>::operator*() const
    {
        return Registry::getComponent<componentType>(owner);
    }

    template<typename componentType>
    inline R_ALWAYS_INLINE pointer<componentType> component<componentType>::operator->()
    {
        return &Registry::getComponent<componentType>(owner);
    }

    template<typename componentType>
    inline R_ALWAYS_INLINE const pointer<componentType> component<componentType>::operator->() const
    {
        return &Registry::getComponent<componentType>(owner);
    }

    template<typename componentType>
    inline R_ALWAYS_INLINE bool component<componentType>::operator==(const component& other) const noexcept
    {
        return owner == other.owner;
    }

    template<typename componentType>
    inline R_ALWAYS_INLINE componentType& component<componentType>::get()
    {
        return Registry::getComponent<componentType>(owner);
    }

    template<typename componentType>
    inline R_ALWAYS_INLINE const componentType& component<componentType>::get() const
    {
        return Registry::getComponent<componentType>(owner);
    }

    template<typename componentType>
    inline R_ALWAYS_INLINE void component<componentType>::destroy()
    {
        Registry::destroyComponent<componentType>(owner);
    }
}
