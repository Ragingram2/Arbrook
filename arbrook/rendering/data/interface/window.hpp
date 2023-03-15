#pragma once
#include <string>

#include <GLFW/glfw3.h>

#include "core/math/math.hpp"

namespace rythe::rendering
{
	template<typename APIType>
	struct Iwindow
	{
	private:
		APIType m_impl;
	public:
		GLFWwindow* getWindow() { return m_impl.getWindow(); }

		void initialize(math::ivec2 res, const std::string& name) { m_imple.initialize(res, name); }

		void swapBuffers() { m_impl.swapBuffers(); }

		void setSwapInterval(int interval) { m_impl.setSwapInterval(interval); }

		void pollEvents() { m_impl.pollEvents(); }

		bool shouldClose() { return m_impl.shouldClose(); }
	};
}