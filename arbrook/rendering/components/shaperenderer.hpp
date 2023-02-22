#pragma once
#include "rendering/data/buffer.hpp"

namespace rythe::rendering
{
	struct shape_renderer
	{
		buffer<vertex, float> vertexBuffer;
		buffer<index, unsigned int> indexBuffer;
	};
}