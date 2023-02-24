#pragma once
#include "rendering/data/vertexarray.hpp"
#include "rendering/data/texture.hpp"
#include "rendering/data/shader.hpp"

namespace rythe::rendering
{
	struct sprite_renderer
	{
		texture m_texture;
		//shader m_shader;
		vertexarray vao;
	};
}