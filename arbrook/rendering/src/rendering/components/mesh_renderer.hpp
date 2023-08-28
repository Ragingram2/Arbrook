#pragma once
#include "core/components/property.hpp"
#include "rendering/interface/definitions.hpp"
#include "rendering/cache/buffercache.hpp"
#include "rendering/data/handles/handles.hpp"
#include "rendering/data/mesh.hpp"
#include "rendering/data/material.hpp"

namespace rythe::rendering
{
	struct mesh_renderer
	{
	private:
		//bool m_instanced = true;
	public:
		material m_material;
		model m_model;
		mesh m_mesh;
		inputlayout layout;

		//mesh_renderer() :
		//	vertexBuffer(&m_model.vertexBuffer), uvBuffer(&m_model.uvBuffer), indexBuffer(&m_model.indexBuffer), matrixBuffer(&m_model.matrixBuffer),
		//	shader(&m_material.m_shader), texture(&m_material.m_texture) { }

		//core::Property<mesh_renderer, buffer_handle> vertexBuffer;
		//core::Property<mesh_renderer, buffer_handle> uvBuffer;
		//core::Property<mesh_renderer, buffer_handle> indexBuffer;
		//core::Property<mesh_renderer, buffer_handle> matrixBuffer;

		//core::Property<mesh_renderer, shader_handle> shader;
		//core::Property<mesh_renderer, texture_handle> texture;

		void initialize(internal::window& hwnd)
		{
			layout.initialize(hwnd, 1, m_material.m_shader);

			m_model.vertexBuffer = BufferCache::createBuffer<math::vec4>("Vertex Buffer", TargetType::VERTEX_BUFFER, UsageType::STATICDRAW, m_mesh.vertices);
			layout.setAttributePtr(m_model.vertexBuffer, "POSITION", 0, FormatType::RGBA32F, 0, sizeof(math::vec4), 0);

			m_model.uvBuffer = BufferCache::createBuffer<math::vec2>("UV Buffer", TargetType::VERTEX_BUFFER, UsageType::STATICDRAW, m_mesh.texCoords);
			layout.setAttributePtr(m_model.uvBuffer, "TEXCOORD", 1, FormatType::RG32F, 0, sizeof(math::vec2), 0);

			m_model.matrixBuffer = BufferCache::createBuffer<math::mat4>("Matrix Buffer", TargetType::VERTEX_BUFFER);
			layout.setAttributePtr(m_model.matrixBuffer, "MODEL", 2, FormatType::RGBA32F, 1, sizeof(math::mat4), 0.f * sizeof(math::vec4), InputClass::PER_INSTANCE, 1);
			layout.setAttributePtr(m_model.matrixBuffer, "MODEL", 3, FormatType::RGBA32F, 1, sizeof(math::mat4), 1.f * sizeof(math::vec4), InputClass::PER_INSTANCE, 1);
			layout.setAttributePtr(m_model.matrixBuffer, "MODEL", 4, FormatType::RGBA32F, 1, sizeof(math::mat4), 2.f * sizeof(math::vec4), InputClass::PER_INSTANCE, 1);
			layout.setAttributePtr(m_model.matrixBuffer, "MODEL", 5, FormatType::RGBA32F, 1, sizeof(math::mat4), 3.f * sizeof(math::vec4), InputClass::PER_INSTANCE, 1);
			layout.submitAttributes();
		}

		void set_mesh(mesh msh)
		{
			m_mesh = msh;
		}
		void set_material(material mat)
		{
			m_material = mat;
		}

		void bind()
		{
			layout.bind();
			//m_model.bind();
			m_material.bind();
			m_model.vertexBuffer->bind();
		}
	};
}