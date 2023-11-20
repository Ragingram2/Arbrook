#pragma once

#include "rendering/data/meshhandle.hpp"
#include "rendering/data/shaderhandle.hpp"
#include "rendering/data/bufferhandle.hpp"

#include "rendering/interface/definitions/buffer.hpp"
#include "rendering/interface/definitions/inputlayout.hpp"
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
		std::string name;
		inputlayout layout;
		buffer_handle indexBuffer;
		buffer_handle vertexBuffer;
		buffer_handle colorBuffer;
		buffer_handle normalBuffer;
		buffer_handle tangentBuffer;
		buffer_handle uvBuffer;
		buffer_handle matrixBuffer;
		buffer_handle cameraBuffer;
		mesh_handle meshHandle;


		model() = default;
		model(const model& mod) : name(mod.name), indexBuffer(mod.indexBuffer), vertexBuffer(mod.vertexBuffer), colorBuffer(mod.colorBuffer), normalBuffer(mod.normalBuffer), tangentBuffer(mod.tangentBuffer), uvBuffer(mod.uvBuffer), matrixBuffer(mod.matrixBuffer) { }

		void initialize(shader_handle shader, mesh_handle handle, bool instanced)
		{
			meshHandle = handle;
			layout.release();
			layout.initialize(1, shader);
			layout.bind();

			vertexBuffer = BufferCache::createBuffer<math::vec4>("Vertex Buffer", TargetType::VERTEX_BUFFER, UsageType::STATICDRAW, meshHandle->vertices);
			layout.setAttributePtr(vertexBuffer, "POSITION", 0, FormatType::RGBA32F, 0, sizeof(math::vec4), 0);

			indexBuffer = BufferCache::createBuffer<unsigned int>("Index Buffer", TargetType::INDEX_BUFFER, UsageType::STATICDRAW, meshHandle->indices);

			normalBuffer = BufferCache::createBuffer<math::vec3>("Normal Buffer", TargetType::VERTEX_BUFFER, UsageType::STATICDRAW, meshHandle->normals);
			layout.setAttributePtr(normalBuffer, "NORMAL", 1, FormatType::RGB32F, 0, sizeof(math::vec3), 0);

			cameraBuffer = BufferCache::createBuffer<camData>("ConstantBuffer", TargetType::CONSTANT_BUFFER, UsageType::STATICDRAW);
			shader->addBuffer(ShaderType::VERTEX, cameraBuffer);
			shader->bind();

			if (meshHandle->texCoords.size() > 0)
			{
				uvBuffer = BufferCache::createBuffer<math::vec2>("UV Buffer", TargetType::VERTEX_BUFFER, UsageType::STATICDRAW, meshHandle->texCoords);
				layout.setAttributePtr(uvBuffer, "TEXCOORD", 2, FormatType::RG32F, 0, sizeof(math::vec2), 0);
			}

			if (instanced)
			{
				matrixBuffer = BufferCache::createBuffer<math::mat4>("Matrix Buffer", TargetType::VERTEX_BUFFER);
				layout.setAttributePtr(matrixBuffer, "MODEL", 3, FormatType::RGBA32F, 1, sizeof(math::mat4), 0.f * sizeof(math::vec4), InputClass::PER_INSTANCE, 1);
				layout.setAttributePtr(matrixBuffer, "MODEL", 4, FormatType::RGBA32F, 1, sizeof(math::mat4), 1.f * sizeof(math::vec4), InputClass::PER_INSTANCE, 1);
				layout.setAttributePtr(matrixBuffer, "MODEL", 5, FormatType::RGBA32F, 1, sizeof(math::mat4), 2.f * sizeof(math::vec4), InputClass::PER_INSTANCE, 1);
				layout.setAttributePtr(matrixBuffer, "MODEL", 6, FormatType::RGBA32F, 1, sizeof(math::mat4), 3.f * sizeof(math::vec4), InputClass::PER_INSTANCE, 1);
			}
			layout.submitAttributes();
		}

		void loadData()
		{
			//layout.bind();
			//vertexBuffer->bufferData(meshHandle->vertices.data(), meshHandle->vertices.size());
			//indexBuffer->bufferData(meshHandle->indices.data(), meshHandle->indices.size());
			//if (meshHandle->texCoords.size() > 0)
			//{
			//	uvBuffer->bufferData(meshHandle->texCoords.data(),meshHandle->texCoords.size());
			//}
		}

		void bind()
		{
			layout.bind();
			if (vertexBuffer != nullptr)
			{
				vertexBuffer->bind();
				vertexBuffer->bufferData(meshHandle->vertices.data(), meshHandle->vertices.size());
			}
			if (indexBuffer != nullptr)
			{
				indexBuffer->bind();
				indexBuffer->bufferData(meshHandle->indices.data(), meshHandle->indices.size());
			}
			if (normalBuffer != nullptr)
			{
				normalBuffer->bind();
				normalBuffer->bufferData(meshHandle->normals.data(), meshHandle->normals.size());
			}
			if (uvBuffer != nullptr)
			{
				uvBuffer->bind();
				uvBuffer->bufferData(meshHandle->texCoords.data(), meshHandle->texCoords.size());
			}
			if (matrixBuffer != nullptr)
				matrixBuffer->bind();
		}
	};

}