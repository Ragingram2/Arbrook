#include "ecs/component.hpp"
#pragma once

namespace rythe::core::ecs
{
    //template<typename componentType>
    //inline R_ALWAYS_INLINE component<componentType>& component<componentType>::operator=(const componentType& src)
    //{
    //    owner.getComponent<componentType>() = src;
    //    return *this;
    //}

    //template<typename componentType>
    //inline R_ALWAYS_INLINE component<componentType>& component<componentType>::operator=(componentType&& src)
    //{
    //    owner.getComponent<componentType>() = std::move(src);
    //    return *this;
    //}

    //template<typename componentType>
    //inline R_ALWAYS_INLINE component<componentType>::operator componentType& ()
    //{
    //    return owner.getComponent<componentType>();
    //}

    //template<typename componentType>
    //inline R_ALWAYS_INLINE component<componentType>::operator const componentType& () const
    //{
    //    return owner.getComponent<componentType>();
    //}

    //template<typename componentType>
    //inline R_ALWAYS_INLINE bool component<componentType>::valid() const noexcept
    //{
    //    return owner.hasComponent<componentType>();
    //}

    //template<typename componentType>
    //inline R_ALWAYS_INLINE component<componentType>::operator bool() const noexcept
    //{
    //    return owner.hasComponent<componentType>();
    //}

    //template<typename componentType>
    //R_NODISCARD componentType& component<componentType>::operator*()
    //{
    //    return owner.getComponent<componentType>();
    //}

    //template<typename componentType>
    //R_NODISCARD const componentType& component<componentType>::operator*() const
    //{
    //    return owner.getComponent<componentType>();
    //}

    //template<typename componentType>
    //inline R_ALWAYS_INLINE pointer<componentType> component<componentType>::operator->()
    //{
    //    return &owner.getComponent<componentType>();
    //}

    //template<typename componentType>
    //inline R_ALWAYS_INLINE const pointer<componentType> component<componentType>::operator->() const
    //{
    //    return &owner.getComponent<componentType>();
    //}

    //template<typename componentType>
    //inline R_ALWAYS_INLINE bool component<componentType>::operator==(const component& other) const noexcept
    //{
    //    return owner == other.owner;
    //}

    //template<typename componentType>
    //inline R_ALWAYS_INLINE componentType& component<componentType>::get()
    //{
    //    return owner.getComponent<componentType>();
    //}

    //template<typename componentType>
    //inline R_ALWAYS_INLINE const componentType& component<componentType>::get() const
    //{
    //    return owner.getComponent<componentType>();
    //}

    //template<typename componentType>
    //inline R_ALWAYS_INLINE void component<componentType>::destroy()
    //{
    //    owner.destroyComponent<componentType>();
    //}
}
