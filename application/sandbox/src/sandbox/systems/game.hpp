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

		math::vec3 inputVec;
		math::vec3 cameraFront;
		float speed = .1f;
		float angularSpeed = 1.f;
		float degrees = 0.0f;

		float deltaTime = 0.0f;
		float lastFrame = 0.0f;
		float currentFrame = 0.0f;

		double lastX = 0;
		double lastY = 0;

		double yaw = 0;
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