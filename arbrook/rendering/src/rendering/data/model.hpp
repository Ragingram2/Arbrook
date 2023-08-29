#pragma once
#include "rendering/data/handles.hpp"
#include "rendering/data/bufferhandle.hpp"

namespace rythe::rendering
{
	struct model
	{
		buffer_handle indexBuffer;
		buffer_handle vertexBuffer;
		buffer_handle colorBuffer;
		buffer_handle normalBuffer;
		buffer_handle tangenBuffer;
		buffer_handle uvBuffer;
		buffer_handle matrixBuffer;

		void bind()
		{
			vertexBuffer->bind();
			uvBuffer->bind();
			matrixBuffer->bind();
		}
	};

}