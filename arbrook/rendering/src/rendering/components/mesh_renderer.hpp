#pragma once
#include "rendering/interface/definitions.hpp"
#include "rendering/data/handles/handles.hpp"
#include "rendering/data/mesh.hpp"

namespace rythe::rendering
{
	struct tex_vtx
	{
		math::vec3 position;
		math::vec2 uv;
	};

	struct mesh_renderer
	{
		model_handle model;
		mesh mesh;
		inputlayout layout;
		texture_handle texture;
		shader_handle shader;
		buffer_handle vertexBuffer;

		void bind()
		{
			texture->bind();
			shader->bind();
			layout.bind();
		}
	};
}