#pragma once
#include <rsl/primitives>
#include <rsl/utilities>

namespace rythe::core::ecs
{
	struct component_base
	{
		rsl::id_type typeId;
	};
}