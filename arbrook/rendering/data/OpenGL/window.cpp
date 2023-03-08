#include "rendering/data/OpenGL/window.hpp"

namespace rythe::rendering::internal
{
	GLFWwindow* window::m_window;

	void window::initialize(math::ivec2 res, const std::string& name)
	{
		m_window = glfwCreateWindow(res.x, res.y, name.c_str(), NULL, NULL);
	}

	void window::swapBuffers()
	{
		glfwSwapBuffers(m_window);
	}

	void window::setSwapInterval(int interval)
	{
		glfwSwapInterval(interval);
	}

	void window::pollEvents()
	{
		glfwPollEvents();
	}

	bool window::shouldClose()
	{
		return glfwWindowShouldClose(m_window);
	}

	void window::makeCurrent()
	{
		glfwMakeContextCurrent(m_window);
	}
}