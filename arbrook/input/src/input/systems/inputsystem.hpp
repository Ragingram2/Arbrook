#pragma once
#include <gainput/gainput.h>
#define GAINPUT_PLATFORM_WIN

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <rsl/math>

#include "core/systems/system.hpp"
#include "core/components/transform.hpp"
#include "input/map/inputmap.hpp"
#include "input/events/inputevents.hpp"

namespace rythe::input
{
	//Figure out what to do here
	class InputSystem : public core::System<int>
	{
	private:
		static GLFWwindow* m_windowHandle;
		static bool m_initialize;
		gainput::InputMap* map;
		gainput::InputManager* m_manager;
		gainput::DeviceId mouseId;
		gainput::DeviceId keyboardId; 
		int width, height;
		math::vec2 mousePos;
		math::vec2 lastMousePos;
		math::vec2 mouseDelta;
	public:
		static bool mouseCaptured;
		void setup();
		void update();
		void shutdown();

		static void registerWindow(GLFWwindow* windowHandle);
	};
}