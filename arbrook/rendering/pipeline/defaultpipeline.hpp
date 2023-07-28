#pragma once
#include "rendering/pipeline/base/pipeline.hpp"
#include "rendering/pipeline/stages/clearstage.hpp"
#include "rendering/pipeline/stages/renderstage.hpp"
#include "rendering/pipeline/stages/guistage.hpp"

namespace rythe::rendering
{

	class DefaultPipeline : public Pipeline<DefaultPipeline>
	{
		virtual void setup() override
		{
			attachStage<render_stage>();
			attachStage<clear_stage>();
			attachStage<gui_stage>();

			RI.initialize(math::vec2(Screen_Width, Screen_Height), "Arbrook");
		}
	};
}