#pragma once
#include <string>

#include <rsl/containers>
#include <rsl/primitives>

#include "core/ecs/entity.hpp"

namespace rythe::core::ecs
{
	struct entity_data
	{
		rsl::id_type id = 0;
		std::string name = "";
		bool alive = true;
		entity parent = { nullptr };
		rsl::hashed_sparse_set<entity> children;
	};
}