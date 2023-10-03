#pragma once
#include "core/core.hpp"
#include "rendering/rendering.hpp"

namespace rythe::game
{
	using namespace rythe::core::events;
	class Game : public core::System<core::transform, gfx::mesh_renderer>
	{
	private:
		core::ecs::entity camera;
		core::ecs::entity ent;
		gfx::material mat;
		gfx::mesh msh;

		math::vec3 camPos = math::vec3::zero;

		math::vec3 inputVec;
		math::vec3 cameraUp = math::vec3::up;
		math::vec3 cameraFront = math::vec3::forward;
		float speed = 2.5f;
		float angularSpeed = 1.f;
		float degrees = 0.0f;

		float deltaTime = 0.0f;
		float lastFrame = 0.0f;
		float currentFrame = 0.0f;

		double lastX = Screen_Width/2.f;
		double lastY = Screen_Height/2.f;

		double yaw = -90.f;
		double pitch = 0;

		bool firstMouse = true;

	public:
		void setup();
		void update();

		void reloadShaders(core::events::key_input& input);
		void move(core::events::key_input& input);
		void mouselook(core::events::mouse_input& input);
		void debugInfo(core::events::key_input& input);
	};
}