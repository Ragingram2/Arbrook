#include "inputsystem.hpp"

namespace rythe::input
{
	GLFWwindow* InputSystem::m_windowHandle;
	bool InputSystem::m_initialize = false;

	void InputSystem::initialize()
	{
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

		map->MapFloat(inputmap::method::W, keyboardId, gainput::KeyW);
		map->MapFloat(inputmap::method::S, keyboardId, gainput::KeyS);
		map->MapFloat(inputmap::method::A, keyboardId, gainput::KeyA);
		map->MapFloat(inputmap::method::D, keyboardId, gainput::KeyD);
		map->MapFloat(inputmap::method::E, keyboardId, gainput::KeyE);
		map->MapFloat(inputmap::method::Q, keyboardId, gainput::KeyQ);

		map->MapBool(inputmap::method::F1, keyboardId, gainput::KeyF1);
		m_initialize = false;
	}

	void InputSystem::update()
	{
		if (!m_windowHandle)
			return;
		else if (m_initialize)
			initialize();

		m_manager->Update();

		MSG msg;
		while (PeekMessage(&msg, glfwGetWin32Window(m_windowHandle), 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			m_manager->HandleMessage(msg);
		}

		{
			moveInput axisEvnt;
			axisEvnt.m_axes[0] = axis_data{ .value = map->GetFloat(inputmap::method::D) - map->GetFloat(inputmap::method::A) };
			axisEvnt.m_axes[1] = axis_data{ .value = map->GetFloat(inputmap::method::W) - map->GetFloat(inputmap::method::S) };
			axisEvnt.m_axes[2] = axis_data{ .value = map->GetFloat(inputmap::method::E) - map->GetFloat(inputmap::method::Q) };
			EventBus::raiseEvent<moveInput>(axisEvnt);
		}

		{
			key_input<inputmap::method::ESCAPE> keyEvnt{ map->GetBoolIsNew(inputmap::method::ESCAPE) , map->GetBoolPrevious(inputmap::method::ESCAPE) };
			EventBus::raiseEvent<key_input<inputmap::method::ESCAPE>>(keyEvnt);
		}
		{
			key_input<inputmap::method::F1> keyEvnt{ map->GetBool(inputmap::method::F1),map->GetBoolPrevious(inputmap::method::F1) };
			EventBus::raiseEvent<key_input<inputmap::method::F1>>(keyEvnt);
		}
		{
			key_input<inputmap::method::MOUSE_LEFT> keyEvnt{ map->GetBool(inputmap::method::MOUSE_LEFT),map->GetBoolPrevious(inputmap::method::MOUSE_LEFT) };
			EventBus::raiseEvent<key_input<inputmap::method::MOUSE_LEFT>>(keyEvnt);
		}
		{
			key_input<inputmap::method::MOUSE_RIGHT> keyEvnt{ map->GetBool(inputmap::method::MOUSE_RIGHT),map->GetBoolPrevious(inputmap::method::MOUSE_RIGHT) };
			EventBus::raiseEvent<key_input<inputmap::method::MOUSE_RIGHT>>(keyEvnt);
		}


		mousePos = math::vec2(map->GetFloat(inputmap::method::MOUSE_X), map->GetFloat(inputmap::method::MOUSE_Y));
		Input::mousePos = mousePos;
		lastMousePos = math::vec2(map->GetFloatPrevious(inputmap::method::MOUSE_X), map->GetFloatPrevious(inputmap::method::MOUSE_Y));
		Input::lastMousePos = lastMousePos;
		mouseDelta = math::vec2(map->GetFloatDelta(inputmap::method::MOUSE_X), map->GetFloatDelta(inputmap::method::MOUSE_Y));
		Input::mouseDelta = mouseDelta;
		{
			core::events::mouse_input mouseEvnt{ mousePos, lastMousePos, mouseDelta };
			core::events::EventBus::raiseEvent<core::events::mouse_input>(mouseEvnt);
		}


		//if (Input::mouseCaptured)
		//	glfwSetInputMode(m_windowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		//else
		//	glfwSetInputMode(m_windowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
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