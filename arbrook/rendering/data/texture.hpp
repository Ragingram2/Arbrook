#pragma once
#include <string>

#include "core/math/math.hpp"

namespace rythe::rendering
{
	namespace math = core::math;

	struct texture_parameters
	{
		int m_channels;
		math::ivec2 m_resolution;

		int m_wrapModeS;
		int m_wrapModeT;
		int m_minFilterMode;
		int m_magFilterMode;

		texture_parameters() = default;
		texture_parameters(int wrapModeS, int wrapModeT, int minFilterMode, int magFilterMode) : m_wrapModeS(wrapModeS), m_wrapModeT(wrapModeT), m_minFilterMode(minFilterMode), m_magFilterMode(magFilterMode) { }
	};

	namespace math = core::math;
	struct texture
	{
		unsigned int m_id;
		std::string m_name;
		unsigned char* m_data;
		texture_parameters m_params;
		texture() = default;
		texture(unsigned int id, std::string name) : m_id(id), m_name(name) { }
		texture(texture* other)
		{
			m_name = other->m_name;
			m_id = other->m_id;
			m_data = other->m_data;
			m_params = other->m_params;
		}

	};
}