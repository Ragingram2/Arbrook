#pragma once
#include <string>

#include <GLFW/glfw3.h>

#include "core/math/math.hpp"

namespace rythe::rendering::internal
{
	struct window
	{
	private:
		GLFWwindow* m_window;
	public:
		math::ivec2 m_resolution;
		std::string m_windowName;

	public:
		window() = default;
		window(math::ivec2 res, const std::string& name) : m_resolution(res), m_windowName(name) { }

		GLFWwindow* getWindow()
		{
			return m_window;
		}

		void initialize(math::ivec2 res, const std::string& name)
		{
			m_window = glfwCreateWindow(res.x, res.y, name.c_str(), NULL, NULL);
		}

		void swapBuffers()
		{
			glfwSwapBuffers(m_window);
		}

		void setSwapInterval(int interval)
		{
			glfwSwapInterval(interval);
		}

		void pollEvents()
		{
			glfwPollEvents();
		}

		bool shouldClose()
		{
			return glfwWindowShouldClose(m_window);
		}

		void makeCurrent()
		{
			glfwMakeContextCurrent(m_window);
		}
	};

}