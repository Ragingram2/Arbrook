#pragma once
#include <string>

#include "core/math/math.hpp"
#include "rendering/interface/definitions/enumtypes.hpp"

namespace rythe::rendering
{
	struct texture_parameters
	{
		int channels;
		math::ivec2 resolution;

		WrapMode wrapModeS;
		WrapMode wrapModeT;
		FilterMode filterMode;
		FormatType format;
		int mipLevels;

		texture_parameters() = default;
		texture_parameters(WrapMode wrapModeS, WrapMode wrapModeT, FilterMode filterMode, FormatType format, int mipLevels = 0) : wrapModeS(wrapModeS), wrapModeT(wrapModeT), filterMode(filterMode), format(format), mipLevels(mipLevels) { }
	};
}