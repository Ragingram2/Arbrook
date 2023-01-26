#pragma once
#include <rythe/primitives>

#include "platform/platform.hpp"

namespace rythe::core::ecs
{
	struct component_base
	{
		rsl::id_type typeId;
	};
}