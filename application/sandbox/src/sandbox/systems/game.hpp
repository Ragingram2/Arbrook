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
		float speed = .1f;
		float angularSpeed = .01f;
		float degrees = 1.0f;

		float deltaTime = 0.0f;
		float lastFrame = 0.0f;
		float currentFrame = 0.0f;

	public:
		void setup();
		void update();

		void reloadShaders(core::events::key_input& input)
		{
			if (input.action == GLFW_PRESS)
			{
				switch (input.key)
				{
				case GLFW_KEY_1:
					gfx::ShaderCache::reloadShaders();
					break;
				}
			}
		}

		void move(core::events::key_input& input)
		{
			inputVec = math::vec3(0.0f);
			if (input.action == GLFW_PRESS)
			{
				log::debug("Key Pressed");
				switch (input.key)
				{
				case GLFW_KEY_D:
				case GLFW_KEY_RIGHT:
					inputVec.x = -speed;
					break;
				case GLFW_KEY_A:
				case GLFW_KEY_LEFT:
					inputVec.x = speed;
					break;
				case GLFW_KEY_W:
				case GLFW_KEY_UP:
					inputVec.z = -speed;
					break;
				case GLFW_KEY_S:
				case GLFW_KEY_DOWN:
					inputVec.z = speed;
					break;
				case GLFW_KEY_E:
					degrees -= angularSpeed;
					break;
				case GLFW_KEY_Q:
					degrees += angularSpeed;
					break;
				}
			}

			//if (input.action == GLFW_RELEASE)
			//{
			//	switch (input.key)
			//	{
			//	case GLFW_KEY_RIGHT:
			//	case GLFW_KEY_LEFT:
			//		inputVec.x = 0;
			//		break;
			//	case GLFW_KEY_UP:
			//	case GLFW_KEY_DOWN:
			//		inputVec.z = 0;
			//		break;
			//	}
			//}
		}
	};
}