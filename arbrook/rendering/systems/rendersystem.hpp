#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "core/core.hpp"
#include "core/events/defaults/exit_event.hpp"
#include "rendering/data/buffer.hpp"
#include "rendering/data/shader.hpp"
#include "rendering/data/window.hpp"
#include "rendering/components/spriterenderer.hpp"

namespace rythe::rendering
{
	namespace log = core::log;
	namespace math = core::math;

	class Renderer : public core::System<core::transform, sprite_renderer, core::exampleComp>
	{
	public:
		window m_window;

		unsigned int vao;
		float r = 0;
		float inc = 0.05f;
		Renderer() = default;
		virtual ~Renderer() = default;

		void setup() override;
		void update() override;
		void shutdown() override;

		static void debugCallback(unsigned int source, unsigned int type, unsigned int id, unsigned int  severity, int length, const char* message, const void* userparam);
		static void debugCallbackARB(unsigned int source, unsigned int type, unsigned int id, unsigned int  severity, int length, const char* message, const void* userparam);
		static void debugCallbackAMD(unsigned int id, unsigned int category, unsigned int  severity, int length, const char* message, void* userparam);
	};
}