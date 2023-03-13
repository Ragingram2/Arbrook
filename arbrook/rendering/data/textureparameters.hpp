#pragma once
#include <string>

#include "core/math/math.hpp"

namespace rythe::rendering
{
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
}