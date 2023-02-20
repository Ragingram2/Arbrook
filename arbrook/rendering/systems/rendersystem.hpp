#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "core/systems/system.hpp"
#include "core/engine/program.hpp"
#include "core/events/eventbus.hpp"
#include "core/events/defaults/exit_event.hpp"
#include "rendering/data/buffer.hpp"
#include "rendering/data/shader.hpp"

namespace rythe::rendering
{
	namespace log = core::log;
	namespace math = core::math;

	class Renderer : public core::System<core::transform, core::renderComp>
	{
	public:
		GLFWwindow* window;

		std::unordered_map<std::string, shader> m_shaders;
		float r = 0;
		float inc = 0.05f;
		Renderer() = default;
		virtual ~Renderer() = default;

		void setup() override;
		void update() override;
		void shutdown() override;

		shader& createShader(const std::string& name, const std::string& filepath);
		shader& getShader(const std::string& name);
		void clearLog();
		bool logCall();
	};
}