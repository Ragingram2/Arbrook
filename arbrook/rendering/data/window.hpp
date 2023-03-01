#pragma once
#include <string>

#include <GLFW/glfw3.h>

#include "core/math/math.hpp"

namespace rythe::rendering
{
	namespace math = core::math;
	struct window
	{
	private:
		static GLFWwindow* m_window;
	public:
		math::ivec2 m_resolution;
		std::string m_windowName;

	public:
		window() = default;
		window(math::ivec2 res, const std::string& name) : m_resolution(res), m_windowName(name)
		{
			m_window = glfwCreateWindow(res.x, res.y, name.c_str(), NULL, NULL);
		}

		operator GLFWwindow* () { return m_window; }

		void initialize(math::ivec2 res, const std::string& name);
		void swapBuffers();
		void setSwapInterval(int interval);
		void pollEvents();
		bool shouldClose();

		static void makeCurrent();
	};
}