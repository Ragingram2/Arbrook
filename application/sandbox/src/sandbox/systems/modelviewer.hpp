#pragma once
#include "core/core.hpp"
#include "rendering/rendering.hpp"
#include "input/input.hpp"

namespace rythe::game
{
	using namespace rythe::core::events;
	class ModelViewer : public core::System<core::transform, gfx::mesh_renderer>
	{
	private:
		core::ecs::entity camera;
		core::ecs::entity ent;
		gfx::model_handle modelHandle;
		gfx::material mat;

		math::vec3 camPos = math::vec3::zero;

		math::vec3 inputVec;
		math::vec3 cameraUp = math::vec3::up;
		math::vec3 cameraFront = math::vec3::forward;
		float speed = 50.0f;

		float deltaTime = 0.0f;
		float lastFrame = 0.0f;
		float currentFrame = 0.0f;

		float sensitivity = .1f;

		float lastX = Screen_Width / 2.f;
		float lastY = Screen_Height / 2.f;

		float yaw = -90.0f;
		float pitch = 0.0f;

		bool firstMouse = true;

	public:
		void setup();
		void update();
		void guiRender();
		void setModel(gfx::model_handle handle);

		void reloadShaders(core::events::key_input& input);
		void move(core::events::key_input& input);
		void mouselook(core::events::mouse_input& input);
		void randomShader(core::events::key_input& input);
		void debugInfo(core::events::key_input& input);
	};
}