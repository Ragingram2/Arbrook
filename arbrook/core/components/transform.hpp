#pragma once
#include "core/math/math.hpp"

namespace rythe::core
{
	struct transform
	{
		math::vec3 position = math::vec3(0.0f);
		math::vec3 scale = math::vec3(1.0f);
		math::quat rotation = math::quat(1.0f,0.0f,0.0f,0.0f);
		math::mat4 localMatrix = math::mat4(1.0f);
		math::mat4 worldMatrix = math::mat4(1.0f);
	};
}