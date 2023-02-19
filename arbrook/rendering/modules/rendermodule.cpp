#include "rendering/modules/rendermodule.hpp"

namespace rythe::rendering
{
	void RenderModule::setup()
	{
		log::debug("Initializing Rendering Module");
		reportSystem<Renderer>();
	}
}