#include "rendering/modules/rendermodule.hpp"

namespace rythe::rendering
{
	void RenderModule::setup()
	{
		log::info("Initializing Rendering Module");
		reportSystem<Renderer>();
	}
}