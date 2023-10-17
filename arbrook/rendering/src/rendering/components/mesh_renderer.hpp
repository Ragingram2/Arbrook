#pragma once

#include "core/components/property.hpp"
//#include "rendering/interface/definitions.hpp"
#include "rendering/data/materialhandle.hpp"
#include "rendering/data/modelhandle.hpp"
#include "rendering/data/meshhandle.hpp"

#include "rendering/interface/config.hpp"
#include Window_HPP_PATH 

namespace rythe::rendering
{
	struct mesh_renderer
	{
	private:
		bool m_instanced = true;
	public:
		material_handle m_material;
		model_handle m_model;
		mesh_handle m_mesh;

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
			m_model->initialize(hwnd, m_material->m_shader, m_mesh, m_instanced);
		}

		void set_model(model_handle handle)
		{
			m_model = handle;
		}

		void set_mesh(mesh_handle handle)
		{
			m_mesh = handle;
		}

		void set_material(material_handle mat)
		{
			m_material = mat;
		}

		void bind()
		{
			m_material->bind();
			m_model->bind();
		}
	};
}