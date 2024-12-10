#pragma once

#include <rsl/primitives>
#include <rsl/hash>

#include "core/containers/pointer.hpp"
#include "core/ecs/component_base.hpp"
#include "core/ecs/entity.hpp"

namespace rythe::core::ecs
{
    template<typename componentType>
    struct component : public component_base
    {
        static constexpr rsl::id_type typeId = rsl::type_id<componentType>();

        entity owner;

        component& operator=(const componentType& src);
        component& operator=(componentType&& src);

        [[nodiscard]] operator componentType& ();
        [[nodiscard]] operator const componentType& () const;

        [[nodiscard]] bool valid() const noexcept;
        [[nodiscard]] operator bool() const noexcept;

        [[nodiscard]] componentType& operator*();
        [[nodiscard]] const componentType& operator*() const;

        [[nodiscard]] pointer<componentType> operator->();
        [[nodiscard]] const pointer<componentType> operator->() const;

        bool operator==(const component& other) const noexcept;

        [[nodiscard]] componentType& get();
        [[nodiscard]] const componentType& get() const;

        void destroy();
    };

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