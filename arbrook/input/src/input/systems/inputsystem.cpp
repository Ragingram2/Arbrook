#include "input/systems/inputsystem.hpp"

namespace rythe::input
{
	GLFWwindow* InputSystem::m_windowHandle;
	bool InputSystem::m_initialize = false;
	bool InputSystem::mouseCaptured = true;

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
		map->MapBool(inputmap::method::MOUSE_LEFT, mouseId, gainput::MouseButtonLeft);
		map->MapBool(inputmap::method::MOUSE_RIGHT, mouseId, gainput::MouseButtonRight);
		map->MapBool(inputmap::method::ESCAPE, keyboardId, gainput::KeyEscape);

		map->MapBool(inputmap::method::W, keyboardId, gainput::KeyW);
		map->MapBool(inputmap::method::A, keyboardId, gainput::KeyA);
		map->MapBool(inputmap::method::S, keyboardId, gainput::KeyS);
		map->MapBool(inputmap::method::D, keyboardId, gainput::KeyD);
		map->MapBool(inputmap::method::Q, keyboardId, gainput::KeyQ);
		map->MapBool(inputmap::method::E, keyboardId, gainput::KeyE);
		map->MapBool(inputmap::method::NUM1, keyboardId, gainput::Key1);
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

		{
			core::events::key_input keyEvnt{ inputmap::method::W,map->GetBool(inputmap::method::W) };
			core::events::EventBus::raiseEvent<core::events::key_input>(keyEvnt);
		}
		{
			core::events::key_input keyEvnt{ inputmap::method::A,map->GetBool(inputmap::method::A) };
			core::events::EventBus::raiseEvent<core::events::key_input>(keyEvnt);
		}
		{
			core::events::key_input keyEvnt{ inputmap::method::S,map->GetBool(inputmap::method::S) };
			core::events::EventBus::raiseEvent<core::events::key_input>(keyEvnt);
		}
		{
			core::events::key_input keyEvnt{ inputmap::method::D,map->GetBool(inputmap::method::D) };
			core::events::EventBus::raiseEvent<core::events::key_input>(keyEvnt);
		}
		{
			core::events::key_input keyEvnt{ inputmap::method::Q,map->GetBool(inputmap::method::Q) };
			core::events::EventBus::raiseEvent<core::events::key_input>(keyEvnt);
		}
		{
			core::events::key_input keyEvnt{ inputmap::method::E,map->GetBool(inputmap::method::E) };
			core::events::EventBus::raiseEvent<core::events::key_input>(keyEvnt);
		}

		{
			core::events::key_input keyEvnt{ inputmap::method::MOUSE_LEFT, map->GetBool(inputmap::method::MOUSE_LEFT) };
			core::events::EventBus::raiseEvent<core::events::key_input>(keyEvnt);
		}
		{
			core::events::key_input keyEvnt{ inputmap::method::MOUSE_RIGHT, map->GetBool(inputmap::method::MOUSE_RIGHT) };
			core::events::EventBus::raiseEvent<core::events::key_input>(keyEvnt);
		}

		{
			core::events::key_input keyEvnt{ inputmap::method::NUM1, map->GetBool(inputmap::method::NUM1) };
			core::events::EventBus::raiseEvent<core::events::key_input>(keyEvnt);
		}

		mousePos = math::vec2(map->GetFloat(inputmap::method::MOUSE_X), map->GetFloat(inputmap::method::MOUSE_Y));
		lastMousePos = math::vec2(map->GetFloatPrevious(inputmap::method::MOUSE_X), map->GetFloatPrevious(inputmap::method::MOUSE_Y));
		mouseDelta = math::vec2(map->GetFloatDelta(inputmap::method::MOUSE_X), map->GetFloatDelta(inputmap::method::MOUSE_Y));
		{
			core::events::mouse_input mouseEvnt{ mousePos, lastMousePos, mouseDelta };
			core::events::EventBus::raiseEvent<core::events::mouse_input>(mouseEvnt);
		}

		if (mouseCaptured)
			glfwSetInputMode(m_windowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else
			glfwSetInputMode(m_windowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
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