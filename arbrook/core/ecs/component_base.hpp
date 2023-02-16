#pragma once
#include <rythe/primitives>

#include "core/platform/platform.hpp"

namespace rythe::core::ecs
{
	struct component_base
	{
		rsl::id_type typeId;
	};
}