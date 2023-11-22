#pragma once
#include <rsl/math>

namespace rythe::rendering
{
	struct light
	{
		math::vec3 lightPos;
		math::vec3 lightColor;
	};
}