#pragma once
#include <GLFW/glfw3.h>
#include <GL/GL.h>

#include "core/systems/system.hpp"
#include "core/engine/program.hpp"
#include "core/events/eventbus.hpp"
#include "core/events/defaults/exit_event.hpp"

namespace rythe::rendering
{
	namespace log = core::log;

	class Renderer : public core::System<core::transform,core::renderComp>
	{
	public:
		GLFWwindow* window;
		Renderer() = default;
		virtual ~Renderer() = default;

		void setup() override;
		void update() override;
		void shutdown() override;

		void render();
	};
}