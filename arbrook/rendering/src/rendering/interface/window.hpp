#pragma once
#include <string>

#include <GLFW/glfw3.h>

#include <rsl/math>

namespace rythe::rendering
{
	template<typename APIType>
	struct Iwindow
	{
	private:
		APIType m_impl;
	public:

		void initialize(math::ivec2 res, const std::string& name, GLFWwindow* window = nullptr) { m_imple.initialize(res, name, window); }

		GLFWwindow* getWindow() { return m_impl.getWindow(); }

		void swapBuffers() { m_impl.swapBuffers(); }

		void setSwapInterval(int interval) { m_impl.setSwapInterval(interval); }

		void pollEvents() { m_impl.pollEvents(); }

		bool shouldClose() { return m_impl.shouldClose(); }

		void setWindowTitle(const std::string& name) { m_impl.setWindowTitle(name); }
	};
}