#pragma once
#include <rsl/primitives>
#include <rsl/utilities>

#include "core/logging/logging.hpp"
#include "rendering/cache/cache.hpp"
#include "rendering/interface/definitions.hpp"
#include "rendering/pipeline/base/graphicsstage.hpp"
#include "rendering/components/components.hpp"

namespace rythe::rendering
{
	struct render_stage : public graphics_stage<render_stage, mesh_renderer, core::transform>
	{
		math::mat4 projection = math::perspective(math::radians(45.f), Screen_Width / Screen_Height, .1f, 100.0f);
		math::mat4 view;
		virtual void setup() override
		{
			math::vec4 positions[] =
			{	//positions						
				{ -1.f, 1.0f, 0.0f,1.0f },//0
				{-1.f,-1.0f, 0.0f,1.0f  },//1
				{  1.0f,-1.0f, 0.0f,1.0f },//2
				{ -1.0f, 1.0f, 0.0f ,1.0f},//0
				{  1.0f,-1.0f, 0.0f,1.0f },//2
				{  1.0f, 1.0f, 0.0f,1.0f }//3
			};
			math::vec2 uvs[] =
			{
					{ 0, 1 },
					{ 0, 0 },
					{ 1, 0 },
					{ 0, 1 },
					{ 1, 0 },
					{ 1, 1 }
			};

			for (auto& ent : m_filter)
			{
				auto& renderer = ent.getComponent<mesh_renderer>();
				auto& transf = ent.getComponent<core::transform>();
				view = math::lookAt((math::vec3)transf.position, ((math::vec3)transf.position) + transf.forward(), transf.up());
				math::mat4 mat = { projection * view * ((math::mat4)transf.localMatrix) };
				renderer.shader = ShaderCache::createShader(*RI, "default", "resources/shaders/default.shader");
				renderer.texture = TextureCache::createTexture2D(*RI, "Rythe", "resources/textures/Rythe.png");
				renderer.vertexBuffer = BufferCache::createBuffer<math::vec4>(*RI, "Vertex Buffer", TargetType::VERTEX_BUFFER, UsageType::STATICDRAW, positions, sizeof(positions) / sizeof(math::vec4));
				renderer.uvBuffer = BufferCache::createBuffer<math::vec2>(*RI, "UV Buffer", TargetType::VERTEX_BUFFER, UsageType::STATICDRAW, uvs, sizeof(uvs) / sizeof(math::vec2));
				renderer.matrixBuffer = BufferCache::createBuffer<math::mat4>(*RI, "Matrix Buffer", TargetType::VERTEX_BUFFER, UsageType::STATICDRAW);
				renderer.initialize(RI->getHwnd());
			}
			RI->checkError();
		}

		virtual void render() override
		{
			for (auto& ent : m_filter)
			{
				auto& renderer = ent.getComponent<mesh_renderer>();
				auto& transf = ent.getComponent<core::transform>();
				view = math::lookAt(((math::vec3)transf.position), (transf.position + transf.forward()), transf.up());
				math::mat4 mat = { projection * view * ((math::mat4)transf.localMatrix) };
				buffer_handle buff = renderer.matrixBuffer;
				buff->bufferData(&mat, 1);
				renderer.bind();
				RI->drawArrays(PrimitiveType::TRIANGLESLIST, 0, 6);
			}
			RI->checkError();
		}

		virtual rsl::priority_type priority() override
		{
			return OPAQUE_PRIORITY;
		}
	};
}