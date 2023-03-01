#pragma once
#include "rendering/data/definitions.hpp"

namespace rythe::rendering
{
	struct sprite_renderer
	{
		texture m_texture;
		shader m_shader;
		vertexarray vao;
	};
}