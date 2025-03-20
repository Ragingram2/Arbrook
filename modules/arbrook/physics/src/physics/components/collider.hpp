#pragma once
#include <rsl/math>

namespace rythe::physics
{
	enum ColliderShape
	{
		Box,
		Plane,
		Sphere,
		Capsule,
		Cylinder
	};

	struct collider
	{
		ColliderShape shape;
		math::vec3 bounds;
		bool isTrigger;
	};
}