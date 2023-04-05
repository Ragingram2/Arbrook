#pragma once
#include "core/math/math.hpp"

namespace rythe::rendering
{
	struct vertex
	{
		math::vec3 m_position;
		math::vec4 m_color;
		math::vec2 m_uv;
		vertex() = default;
		vertex(math::vec3 position, math::vec4 color, math::vec2 uv) : m_position(position), m_color(color), m_uv(uv) {}
		~vertex() = default;
	};
}