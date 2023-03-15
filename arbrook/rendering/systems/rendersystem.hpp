#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "core/core.hpp"
#include "core/events/defaults/exit_event.hpp"
#include "rendering/data/definitions.hpp"
#include "rendering/data/shadercache.hpp"
#include "rendering/data/texturecache.hpp"
#include "rendering/components/spriterenderer.hpp"
#include Window_HPP_PATH

namespace rythe::rendering
{
	namespace log = core::log;
	namespace math = core::math;

	class Renderer : public core::System<core::transform, sprite_renderer, core::exampleComp>
	{
	public:
		internal::window m_window;
		RenderInterface m_renderApi;

		Renderer() = default;
		virtual ~Renderer() = default;

		void setup() override;
		void update() override;
		void shutdown() override;

	};
}