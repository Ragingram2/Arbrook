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
        static constexpr rsl::id_type typeId = rsl::typeHash<componentType>();

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
}

#include "core/ecs/component.inl"