#include "rendering/modules/rendermodule.hpp"

namespace rythe::rendering
{
	void RenderModule::setup()
	{
		log::debug("Initialized Rendering Module");
		reportSystem<RenderSystem>();
	}
}