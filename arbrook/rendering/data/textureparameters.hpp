#pragma once
#include <string>

#include "core/math/math.hpp"
#include "rendering/data/interface/enumtypes.hpp"

namespace rythe::rendering
{
	struct texture_parameters
	{
		int m_channels;
		math::ivec2 m_resolution;

		WrapMode m_wrapModeS;
		WrapMode m_wrapModeT;
		FilterMode m_minFilterMode;
		FilterMode m_magFilterMode;

		texture_parameters() = default;
		texture_parameters(WrapMode wrapModeS, WrapMode wrapModeT, FilterMode minFilterMode, FilterMode magFilterMode) : m_wrapModeS(wrapModeS), m_wrapModeT(wrapModeT), m_minFilterMode(minFilterMode), m_magFilterMode(magFilterMode) { }
	};
}