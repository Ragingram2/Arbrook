#pragma once
#include "rendering/data/definitions.hpp"
#include "rendering/data/texturehandle.hpp"
#include "rendering/data/shaderhandle.hpp"

namespace rythe::rendering
{
	struct sprite_renderer
	{
		texture_handle texture;
		shader_handle shader;
		inputlayout layout;

		sprite_renderer() = default;
		sprite_renderer(texture_handle t_handle, shader_handle s_handle) : texture(t_handle), shader(s_handle) {}

	};
}