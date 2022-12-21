#pragma once
#include "platform/platform.hpp"
#include "types/primitives.hpp"

namespace rythe::core::ecs
{
	struct entity_data;

	struct entity
	{
    public:
        entity_data* data;

        template<typename T>
        R_NODISCARD bool operator ==(T val) const;

        template<typename T>
        R_NODISCARD bool operator !=(T val) const;

        R_NODISCARD operator id_type () const noexcept;

        R_NODISCARD bool valid() const noexcept;

        R_NODISCARD entity_data* operator->() noexcept;
        R_NODISCARD const entity_data* operator->() const noexcept;
	};
}