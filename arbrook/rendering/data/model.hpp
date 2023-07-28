#pragma once
#include "rendering/data/handles/bufferhandle.hpp"

namespace rythe::rendering
{
	struct model
	{
	public:
		buffer_handle indexBuffer;
		buffer_handle vertexBuffer;
		buffer_handle colorBuffer;
		buffer_handle normalBuffer;
		buffer_handle tangenBuffer;
		buffer_handle uvBuffer;
		buffer_handle matrixBuffer;
	};

}