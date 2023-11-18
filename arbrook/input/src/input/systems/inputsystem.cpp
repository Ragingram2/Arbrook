#include "input/systems/inputsystem.hpp"

namespace rythe::input
{
	GLFWwindow* InputSystem::m_windowHandle;
	bool InputSystem::m_initialize = false;
	math::vec2 InputSystem::mousePos;
	math::vec2 InputSystem::lastMousePos;
	math::vec2 InputSystem::mouseDelta;

	void InputSystem::setup()
	{
		if (!m_windowHandle)
		{
			log::error("Window Handle was not registered with the input system");
			return;
		}
		log::info("Initializing Input System");
		m_manager = new gainput::InputManager(true);
		mouseId = m_manager->CreateDevice<gainput::InputDeviceMouse>();
		keyboardId = m_manager->CreateDevice<gainput::InputDeviceKeyboard>();
		glfwGetWindowSize(m_windowHandle, &width, &height);
		m_manager->SetDisplaySize(width, height);
		map = new gainput::InputMap(*m_manager, "Testmap");
		map->MapFloat(inputmap::method::MOUSE_X, mouseId, gainput::MouseAxisX, 0, width);
		map->MapFloat(inputmap::method::MOUSE_Y, mouseId, gainput::MouseAxisY, 0, height);
		map->MapBool(inputmap::method::ESCAPE, mouseId, gainput::KeyEscape);
		m_initialize = false;
	}

	void InputSystem::update()
	{
		if (m_initialize)
			setup();

		m_manager->Update();

		MSG msg;
		while (PeekMessage(&msg, glfwGetWin32Window(m_windowHandle), 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			m_manager->HandleMessage(msg);
		}

		{
			core::events::key_input keyEvnt{ inputmap::method::ESCAPE,map->GetBoolIsNew(inputmap::method::ESCAPE) };
			core::events::EventBus::raiseEvent<core::events::key_input>(keyEvnt);
		}

		mousePos = math::vec2(map->GetFloat(inputmap::method::MOUSE_X), map->GetFloat(inputmap::method::MOUSE_Y));
		lastMousePos = math::vec2(map->GetFloatPrevious(inputmap::method::MOUSE_X), map->GetFloatPrevious(inputmap::method::MOUSE_Y));
		mouseDelta = math::vec2(map->GetFloatDelta(inputmap::method::MOUSE_X), map->GetFloatDelta(inputmap::method::MOUSE_Y));
		{
			core::events::mouse_input mouseEvnt{ mousePos, lastMousePos, mouseDelta };
			core::events::EventBus::raiseEvent<core::events::mouse_input>(mouseEvnt);
		}
	}

	void InputSystem::shutdown()
	{

	}

	void InputSystem::registerWindow(GLFWwindow* windowHandle)
	{
		m_windowHandle = windowHandle;
		m_initialize = true;
	}
}