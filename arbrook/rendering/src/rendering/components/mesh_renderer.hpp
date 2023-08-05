#pragma once
#include "core/components/property.hpp"
#include "rendering/interface/definitions.hpp"
#include "rendering/data/handles/handles.hpp"
#include "rendering/data/mesh.hpp"

namespace rythe::rendering
{

	struct material
	{
		texture_handle m_texture;
		shader_handle m_shader;

		void bind()
		{
			m_texture->bind();
			m_shader->bind();
		}
	};

	struct mesh_renderer
	{
	private:
		model m_model;
		mesh m_mesh;
		inputlayout m_layout;
		material m_material;

	public:
		mesh_renderer() :
			vertexBuffer(&m_model.vertexBuffer), uvBuffer(&m_model.uvBuffer), indexBuffer(&m_model.indexBuffer), matrixBuffer(&m_model.matrixBuffer),
			shader(&m_material.m_shader), texture(&m_material.m_texture),
			layout(&m_layout) { }
		core::Property<mesh_renderer, buffer_handle> vertexBuffer;
		core::Property<mesh_renderer, buffer_handle> uvBuffer;
		core::Property<mesh_renderer, buffer_handle> indexBuffer;
		core::Property<mesh_renderer, buffer_handle> matrixBuffer;

		core::Property<mesh_renderer, shader_handle> shader;
		core::Property<mesh_renderer, texture_handle> texture;

		core::Property<mesh_renderer, inputlayout> layout;

		void initialize(internal::window& hwnd)
		{
			m_material.bind();
			m_layout.initialize(hwnd, 1, m_material.m_shader);
			m_layout.setAttributePtr(m_model.vertexBuffer, "POSITION", 0, FormatType::RGB32F, 0, sizeof(math::vec4), 0);
			m_layout.setAttributePtr(m_model.uvBuffer, "TEXCOORD", 1, FormatType::RG32F, 0, sizeof(math::vec2), 0);

			m_layout.setAttributePtr(m_model.matrixBuffer, "MODEL", 0, FormatType::RGBA32F, 1, sizeof(math::mat4), 0.f * sizeof(math::vec4), InputClass::PER_INSTANCE, 1);
			m_layout.setAttributePtr(m_model.matrixBuffer, "MODEL", 1, FormatType::RGBA32F, 1, sizeof(math::mat4), 1.f * sizeof(math::vec4), InputClass::PER_INSTANCE, 1);
			m_layout.setAttributePtr(m_model.matrixBuffer, "MODEL", 2, FormatType::RGBA32F, 1, sizeof(math::mat4), 2.f * sizeof(math::vec4), InputClass::PER_INSTANCE, 1);
			m_layout.setAttributePtr(m_model.matrixBuffer, "MODEL", 3, FormatType::RGBA32F, 1, sizeof(math::mat4), 3.f * sizeof(math::vec4), InputClass::PER_INSTANCE, 1);
			m_layout.submitAttributes();
		}

		void set_material(material mat)
		{
			m_material = mat;
		}

		void bind()
		{
			m_material.bind();
			m_layout.bind();
			m_model.bind();

		}
	};
}