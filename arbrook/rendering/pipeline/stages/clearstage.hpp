#pragma once
#include "rendering/pipeline/base/graphicsstage.hpp"

namespace rythe::rendering
{
	struct clear_stage : public graphics_stage<clear_stage>
	{
		virtual void setup() override
		{
			RI->setSwapInterval(0);
			RI->setViewport(1, 0, 0, Screen_Width, Screen_Height, 0, 1);
			RI->setClearColor(0x64 / 255.0f, 0x95 / 255.0f, 0xED / 255.0f, 1.0f);
		}

		virtual void render() override
		{
			RI->clear(ClearBit::COLOR);
		}

		virtual rsl::priority_type priority() override
		{
			return CLEAR_PRIORITY;
		}
	};
}