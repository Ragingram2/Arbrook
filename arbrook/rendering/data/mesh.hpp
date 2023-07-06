#pragma once
#include <vector>

#include "core/math/math.hpp"

#include "rendering/data/vertex.hpp"

namespace rythe::rendering
{
	struct mesh
	{
		std::vector<math::vec3> vertices;
		std::vector<unsigned int> indices;
		std::vector<math::vec2> texCoords;
	};
}