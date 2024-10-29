#pragma once
#include <gainput/gainput.h>
#define GAINPUT_PLATFORM_WIN

#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <rsl/math>

#include "core/systems/system.hpp"
#include "core/components/transform.hpp"
#include "../map/inputmap.hpp"
#include "../events/inputevents.hpp"

namespace rythe::input
{
	using namespace rythe::core::events;
	using moveInput = axis_input < axis_data{ inputmap::method::A, inputmap::method::D, 1, -1, 0 }, axis_data{ inputmap::method::W, inputmap::method::S, 1, -1, 0 }, axis_data{ inputmap::method::Q, inputmap::method::E, 1, -1, 0 } > ;

	struct Input
	{
		inline static math::vec2 mousePos;
		inline static math::vec2 lastMousePos;
		inline static math::vec2 mouseDelta;
		inline static bool mouseCaptured = true;
		inline static bool wasPressed = false;
		inline static bool isPressed = false;
	};

	class InputSystem : public core::System<InputSystem, int>
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

		void initialize();
		void update();
		void shutdown();

		static void registerWindow(GLFWwindow* windowHandle);
	};
}