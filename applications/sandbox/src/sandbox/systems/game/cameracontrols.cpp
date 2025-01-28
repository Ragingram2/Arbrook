#include "cameracontrols.hpp"

namespace rythe::game
{
	void CameraControls::setup()
	{
		bindEvent<moveInput, &CameraControls::move>();
		bindEvent<mouse_input, &CameraControls::mouselook>();

		for (auto& ent : m_filter)
		{
			camera = ent;
			break;
		}
	}

	void CameraControls::update()
	{
		ZoneScopedN("Camera Controls");
		if (camera == invalid_id) return;

		for (auto& ent : m_filter)
		{
			if (!Input::mouseCaptured) continue;

			auto& camTransf = ent.getComponent<core::transform>();
			camTransf.rotation = math::quat::from_euler(math::vec3(math::deg2rad(pitch), math::deg2rad(yaw), 0.0f));
		}
	}

	void CameraControls::move(moveInput& input)
	{
		if (camera == invalid_id) return;

		for (auto& ent : m_filter)
		{
			auto& camSettings = ent.getComponent<camera_settings>();
			auto& transf = ent.getComponent<core::transform>();

			auto leftRight = input.getValue(0);
			auto forwardBackward = input.getValue(1);
			auto upDown = input.getValue(2);
			auto velocity = transf.right() * leftRight;
			velocity += transf.forward() * forwardBackward;
			velocity += transf.up() * upDown;
			if (math::length(velocity) > 0.0f)
			{
				velocity = math::normalize(velocity) * camSettings.speed * core::Time::deltaTime;
				transf.position += velocity;
			}
		}
	}

	void CameraControls::mouselook(mouse_input& input)
	{
		if (camera == invalid_id) return;

		if (!Input::mouseCaptured) return;

		for (auto& ent : m_filter)
		{
			auto& camSettings = ent.getComponent<camera_settings>();
			switch (camSettings.mode)
			{
			case CameraControlMode::FreeLook:
				freeLook(ent, input);
				break;
			case CameraControlMode::Orbit:
				orbit(ent, input);
				break;
			default:
				break;
			}
		}

	}

	void CameraControls::orbit(core::ecs::entity& ent, mouse_input& input)
	{

	}

	void CameraControls::freeLook(core::ecs::entity& ent, mouse_input& input)
	{
		auto& camSettings = ent.getComponent<camera_settings>();

		static bool firstMouse = true;

		if (firstMouse)
		{
			lastMousePos = input.lastPosition;
			firstMouse = false;
		}

		mousePos = input.position;
		mouseDelta = input.positionDelta;
		lastMousePos = input.lastPosition;

		rotationDelta = math::vec2(mouseDelta.x, mouseDelta.y) * camSettings.sensitivity;

		pitch = math::clamp(pitch + rotationDelta.y, -89.99f, 89.99);
		yaw += rotationDelta.x;
	}
}