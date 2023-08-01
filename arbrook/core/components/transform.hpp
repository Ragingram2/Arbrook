#pragma once
#include "core/math/math.hpp"

namespace rythe::core
{
	struct transform
	{
		math::mat4 localMatrix = math::mat4(1.0f);
		math::mat4 worldMatrix = math::mat4(1.0f);

		math::vec3 up() { return rotation().up(); }
		math::vec3 right() { return rotation().right(); }
		math::vec3 forward() { return rotation().forward(); }

		math::vec3 position() { return math::translation(worldMatrix); }
		math::vec3 scale() { return math::scale(worldMatrix); }
		math::quat rotation() { return math::orientation(worldMatrix); }
	};
}