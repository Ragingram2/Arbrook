#pragma once
#include "core/math/math.hpp"

namespace rythe::rendering
{
	struct vtx_pos_col
	{
		math::vec3 m_position;
		math::vec4 m_color;
		vtx_pos_col() = default;
		vtx_pos_col(math::vec3 position, math::vec4 color) : m_position(position), m_color(color) {}
		~vtx_pos_col() = default;
	};

	struct vertex
	{
		math::vec3 m_position;
		math::vec4 m_color;
		math::vec2 m_uv;
		vertex() = default;
		vertex(math::vec3 position, math::vec4 color, math::vec2 uv) : m_position(position), m_color(color), m_uv(uv) {}
		~vertex() = default;
	};

	struct vtx_constant
	{
		math::vec3 position;
		float time;
	};

}