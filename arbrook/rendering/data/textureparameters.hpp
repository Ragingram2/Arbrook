#pragma once
#include <string>

#include "core/math/math.hpp"
#include "rendering/data/config.hpp"
#include TextureParams_HPP_PATH

namespace rythe::rendering
{
	enum class WrapMode
	{
		CLAMP = static_cast<WrapMode>(internal::WrapMode::CLAMP),
		REPEAT = static_cast<WrapMode>(internal::WrapMode::REPEAT)
	};

	//change the paremeters to enums
	struct texture_parameters
	{
		int m_channels;
		math::ivec2 m_resolution;

		WrapMode m_wrapModeS;
		WrapMode m_wrapModeT;
		int m_minFilterMode;
		int m_magFilterMode;

		texture_parameters() = default;
		texture_parameters(WrapMode wrapModeS, WrapMode wrapModeT, int minFilterMode, int magFilterMode) : m_wrapModeS(wrapModeS), m_wrapModeT(wrapModeT), m_minFilterMode(minFilterMode), m_magFilterMode(magFilterMode) { }
	};
}