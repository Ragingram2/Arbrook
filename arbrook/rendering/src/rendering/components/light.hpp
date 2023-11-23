#pragma once
#include <rsl/math>

namespace rythe::rendering
{
	struct light
	{
		math::vec4 lightPos;
		math::vec4 lightColor;
	};
}