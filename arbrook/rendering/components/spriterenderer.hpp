#pragma once
#include "rendering/data/definitions.hpp"
#include "rendering/data/texturehandle.hpp"
#include "rendering/data/shaderhandle.hpp"

namespace rythe::rendering
{
	struct sprite_renderer
	{
		texture_handle m_texture;
		shader_handle m_shader;
		vertexarray vao;

		sprite_renderer() = default;
		sprite_renderer(texture_handle t_handle, shader_handle s_handle) : m_texture(t_handle), m_shader(s_handle) {}

	};
}