#pragma once

#include "rendering/data/meshhandle.hpp"
#include "rendering/data/shaderhandle.hpp"
#include "rendering/data/bufferhandle.hpp"

#include "rendering/interface/buffer.hpp"
#include "rendering/interface/inputlayout.hpp"
#include "rendering/cache/buffercache.hpp"

namespace rythe::rendering
{
	struct camData
	{
		math::mat4 projection;
		math::mat4 view;
		math::mat4 model;
	};

	struct model
	{
		inputlayout layout;
		buffer_handle indexBuffer;
		buffer_handle vertexBuffer;
		buffer_handle colorBuffer;
		buffer_handle normalBuffer;
		buffer_handle tangentBuffer;
		buffer_handle uvBuffer;
		buffer_handle matrixBuffer;
		buffer_handle cameraBuffer;
		mesh_handle mesh;

		model() = default;
		model(const model& mod) : indexBuffer(mod.indexBuffer), vertexBuffer(mod.vertexBuffer), colorBuffer(mod.colorBuffer), normalBuffer(mod.normalBuffer), tangentBuffer(mod.tangentBuffer), uvBuffer(mod.uvBuffer), matrixBuffer(mod.matrixBuffer) { }

		void initialize(internal::window& hwnd, shader_handle shader, mesh_handle handle, bool instanced)
		{
			layout.initialize(hwnd, 1, shader);
			layout.bind();

			vertexBuffer = BufferCache::createBuffer<math::vec4>("Vertex Buffer", TargetType::VERTEX_BUFFER, UsageType::STATICDRAW, handle->vertices);
			layout.setAttributePtr(vertexBuffer, "POSITION", 0, FormatType::RGBA32F, 0, sizeof(math::vec4), 0);

			indexBuffer = BufferCache::createBuffer<unsigned int>("Index Buffer", TargetType::INDEX_BUFFER, UsageType::STATICDRAW, handle->indices);

			cameraBuffer = BufferCache::createBuffer<camData>("ConstantBuffer", TargetType::CONSTANT_BUFFER, UsageType::STATICDRAW);
			shader->addBuffer(ShaderType::VERTEX, cameraBuffer);
			shader->bind();

			if (handle->texCoords.size() > 0)
			{
				uvBuffer = BufferCache::createBuffer<math::vec2>("UV Buffer", TargetType::VERTEX_BUFFER, UsageType::STATICDRAW, handle->texCoords);
				layout.setAttributePtr(uvBuffer, "TEXCOORD", 1, FormatType::RG32F, 0, sizeof(math::vec2), 0);
			}

			if (instanced)
			{
				matrixBuffer = BufferCache::createBuffer<math::mat4>("Matrix Buffer", TargetType::VERTEX_BUFFER);
				layout.setAttributePtr(matrixBuffer, "MODEL", 2, FormatType::RGBA32F, 1, sizeof(math::mat4), 0.f * sizeof(math::vec4), InputClass::PER_INSTANCE, 1);
				layout.setAttributePtr(matrixBuffer, "MODEL", 3, FormatType::RGBA32F, 1, sizeof(math::mat4), 1.f * sizeof(math::vec4), InputClass::PER_INSTANCE, 1);
				layout.setAttributePtr(matrixBuffer, "MODEL", 4, FormatType::RGBA32F, 1, sizeof(math::mat4), 2.f * sizeof(math::vec4), InputClass::PER_INSTANCE, 1);
				layout.setAttributePtr(matrixBuffer, "MODEL", 5, FormatType::RGBA32F, 1, sizeof(math::mat4), 3.f * sizeof(math::vec4), InputClass::PER_INSTANCE, 1);
			}
			layout.submitAttributes();
		}

		void bind()
		{
			layout.bind();
			if (vertexBuffer != nullptr)
				vertexBuffer->bind();
			if (indexBuffer != nullptr)
				indexBuffer->bind();
			if (uvBuffer != nullptr)
				uvBuffer->bind();
			if (matrixBuffer != nullptr)
				matrixBuffer->bind();
		}
	};

}