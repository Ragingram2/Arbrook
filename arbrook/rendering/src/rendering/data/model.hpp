#pragma once
#include "rendering/data/handles.hpp"
#include "rendering/data/bufferhandle.hpp"
#include "rendering/data/meshhandle.hpp"

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

		void initialize(mesh_handle handle)
		{
			vertexBuffer->bufferData(handle->vertices.data(),handle->vertices.size());
			indexBuffer->bufferData(handle->indices.data(), handle->indices.size());
			colorBuffer->bufferData(handle->colors.data(), handle->colors.size());
			uvBuffer->bufferData(handle->texCoords.data(), handle->texCoords.size());
		}

		void bind()
		{
			vertexBuffer->bind();
			uvBuffer->bind();
			matrixBuffer->bind();
		}
	};

}