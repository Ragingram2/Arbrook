#pragma once
#include <fstream>
#include <string>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "core/systems/system.hpp"
#include "core/engine/program.hpp"
#include "core/events/eventbus.hpp"
#include "core/events/defaults/exit_event.hpp"

namespace rythe::rendering
{
	namespace log = core::log;

	struct shader_source
	{
		std::string vertexSource;
		std::string fragSource;
	};

	class Renderer : public core::System<core::transform, core::renderComp>
	{
	public:
		GLFWwindow* window;
		int loc = 0;
		float r = 0;
		float inc = 0.05f;
		Renderer() = default;
		virtual ~Renderer() = default;

		void setup() override;
		void update() override;
		void shutdown() override;

		unsigned int compileShader(unsigned int type, const std::string& source);

		unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);

		shader_source parseShader(const std::string& file);

		void clearErrors();

		bool logCall();
	};
}