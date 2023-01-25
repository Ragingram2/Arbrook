#pragma once

#include <rythe/primitives>

#include "ecs/entity.hpp"

namespace rythe::core::ecs
{
	struct component_base
	{
		rsl::id_type typeId;
	};

    template<typename componentType>
    struct component : public component_base
    {
        static constexpr rsl::id_type typeId = typeid(componentType).hash_code();

        entity owner;

        component& operator=(const componentType& src);
        component& operator=(componentType&& src);

        R_NODISCARD operator componentType& ();
        R_NODISCARD operator const componentType& () const;

        R_NODISCARD bool valid() const noexcept;
        R_NODISCARD operator bool() const noexcept;

        R_NODISCARD componentType& operator*();
        R_NODISCARD const componentType& operator*() const;

        R_NODISCARD componentType* operator->();
        R_NODISCARD const componentType* operator->() const;

        bool operator==(const component& other) const noexcept;

        R_NODISCARD componentType& get();
        R_NODISCARD const componentType& get() const;

        void destroy();
    };
}

#include "ecs/component.inl"