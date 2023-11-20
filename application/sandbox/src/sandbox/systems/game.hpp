#pragma once
#include "core/core.hpp"
#include "rendering/rendering.hpp"
#include "input/input.hpp"

namespace rythe::game
{
	using namespace rythe::core::events;
	class Game : public core::System<core::transform, gfx::mesh_renderer>
	{
	private:
		core::ecs::entity camera;
		core::ecs::entity cube;
		gfx::model_handle modelHandle;
		gfx::material mat;
		gfx::material lit;

		math::vec3 velocity;

		math::vec2 mousePos;
		math::vec2 lastMousePos;
		math::vec2 mouseDelta;
		math::vec2 rotationDelta;

		math::vec3 front;
		math::vec3 right;
		math::vec3 up;

		float speed = 50.0f;

		float deltaTime = 0.0f;
		float lastFrame = 0.0f;
		float currentFrame = 0.0f;

		float sensitivity = 1.1f;

		float yaw = -90.0f;
		float pitch = 0.0f;

	public:
		void setup();
		void update();
		void guiRender();
		void setModel(gfx::model_handle handle);

		void reloadShaders(core::events::key_input& input);
		void move(core::events::key_input& input);
		void mouselook(core::events::mouse_input& input);

		void toggleMouseCapture(core::events::key_input& input)
		{
			if (input.value)
			{
				if (input.key == inputmap::method::ESCAPE)
				{
					input::InputSystem::mouseCaptured = !input::InputSystem::mouseCaptured;
				}
			}
		}
	};
}