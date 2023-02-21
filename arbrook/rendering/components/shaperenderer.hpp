#pragma once
#include "rendering/data/buffer.hpp"

namespace rythe::rendering
{
	struct shape_renderer
	{
		buffer<float> vertexBuffer;
		buffer<unsigned int> indexBuffer;
	};
}