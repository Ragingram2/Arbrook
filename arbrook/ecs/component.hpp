#pragma once

#include <rythe/primitives>
#include <rythe/hash>

#include "platform/platform.hpp"
#include "containers/pointer.hpp"
#include "ecs/component_base.hpp"
#include "ecs/entity.hpp"

namespace rythe::core::ecs
{
    template<typename componentType>
    struct component : public component_base
    {
      /*  static constexpr rsl::id_type typeId = rsl::typeHash<componentType>();*/

        entity owner;

      /*  component& operator=(const componentType& src);
        component& operator=(componentType&& src);

        R_NODISCARD operator componentType& ();
        R_NODISCARD operator const componentType& () const;

        R_NODISCARD bool valid() const noexcept;
        R_NODISCARD operator bool() const noexcept;

        R_NODISCARD componentType& operator*();
        R_NODISCARD const componentType& operator*() const;

        R_NODISCARD pointer<componentType> operator->();
        R_NODISCARD const pointer<componentType> operator->() const;

        bool operator==(const component& other) const noexcept;

        R_NODISCARD componentType& get();
        R_NODISCARD const componentType& get() const;

        void destroy();*/
    };
}

#include "ecs/component.inl"