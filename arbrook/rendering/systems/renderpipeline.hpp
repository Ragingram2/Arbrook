#pragma once

#include "core/systems/system.hpp"
#include "rendering/data/definitions.hpp"
#include "rendering/components/mesh_renderer.hpp"


namespace rythe::rendering
{
	namespace log = core::log;
	namespace math = core::math;

	class RendererPipeline : public core::System<mesh_renderer>
	{
	public:
		RenderInterface* m_api;
	}
};