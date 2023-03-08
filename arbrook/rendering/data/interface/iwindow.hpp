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
		void initialize(core::math::ivec2 res, const std::string& name) { m_impl.initialize(res, name); }
		void swapBuffers() { m_impl.swapBuffers(); }
		void setSwapInterval(int interval) { m_impl.setSwapInterval(interval); }
		void pollEvents() { m_impl.pollEvents(); }
		bool shouldClose() { return m_impl.shouldClose(); }

		GLFWwindow* getGLFWWindow() { return m_impl.getGLFWWindow(); }

		operator APIType* () { return &m_impl; }

		static void makeCurrent() { APIType::makeCurrent(); }
	};
}