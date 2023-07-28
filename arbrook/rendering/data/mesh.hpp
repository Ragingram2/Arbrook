#pragma once
#include <vector>

#include "core/math/math.hpp"

#include "rendering/data/vertex.hpp"

namespace rythe::rendering
{
	struct sub_mesh
	{
		std::string name;
		rsl::size_type count;
		rsl::size_type offset;
		rsl::int32 materialIdx;
	};

	struct mesh
	{
		std::vector<math::vec3> vertices;
		std::vector<math::vec4> colors;
		std::vector<math::vec3> normals;
		std::vector<math::vec2> texCoords;
		std::vector<unsigned int> indices;
		//std::vecotr<material_data> materials;
		std::vector<sub_mesh> submeshes;
	};
}