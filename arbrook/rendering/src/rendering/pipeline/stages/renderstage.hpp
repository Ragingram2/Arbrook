#pragma once
#include <rsl/primitives>
#include <rsl/utilities>

#include "core/logging/logging.hpp"
#include "rendering/cache/cache.hpp"
#include "rendering/interface/definitions.hpp"
#include "rendering/pipeline/base/graphicsstage.hpp"
#include "rendering/components/mesh_renderer.hpp"

namespace rythe::rendering
{
	struct render_stage : public graphics_stage<render_stage>
	{
		virtual void setup() override
		{
			tex_vtx verticies[] =
			{	//positions						
				{ { -1.f, 1.0f, 0.0f  },	{ 0, 1 } },//0
				{ {-1.f,-1.0f, 0.0f  },	{ 0, 0 } },//1
				{ {  1.0f,-1.0f, 0.0f },		{ 1, 0 } },//2
				{ { -1.0f, 1.0f, 0.0f },		{ 0, 1 } },//0
				{ {  1.0f,-1.0f, 0.0f },		{ 1, 0 } },//2
				{ {  1.0f, 1.0f, 0.0f },		{ 1, 1 } }//3
			};

			for (auto& ent : m_filter)
			{
				auto& renderer = ent.getComponent<mesh_renderer>();
				auto& shader = renderer.shader = ShaderCache::createShader(*RI, "default", "resources/shaders/texture.shader");
				auto& texture = renderer.texture = TextureCache::createTexture2D(*RI, "Rythe", "resources/textures/Rythe.png");
				auto& vBuffer = renderer.vertexBuffer = BufferCache::createBuffer<tex_vtx>(*RI, "Vertex Buffer", TargetType::VERTEX_BUFFER, UsageType::STATICDRAW, verticies, sizeof(verticies) / sizeof(tex_vtx));
				auto& layout = renderer.layout;

				shader->bind();
				texture->bind();
				layout.initialize(RI->getHwnd(), 1, shader);
				layout.setAttributePtr("POSITION", 0, FormatType::RGB32F, 0, sizeof(tex_vtx), 0);
				layout.setAttributePtr("TEXCOORD", 1, FormatType::RG32F, 0, sizeof(tex_vtx), sizeof(math::vec3));
				vBuffer->bind();
				layout.bind();
			}
			RI->checkError();
		}

		virtual void render() override
		{
			for (auto& ent : m_filter)
			{
				auto& renderer = ent.getComponent<mesh_renderer>();
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