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
		float speed = .05f;

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
			if (input.action == GLFW_PRESS)
			{
				switch (input.key)
				{
				case GLFW_KEY_RIGHT:
					inputVec += math::vec3::right*speed;
					break;
				case GLFW_KEY_LEFT:
					inputVec -= math::vec3::right * speed;
					break;
				case GLFW_KEY_UP:
					inputVec += math::vec3::forward * speed;
					break;
				case GLFW_KEY_DOWN:
					inputVec -= math::vec3::forward * speed;
					break;
				}
			}

			if (input.action == GLFW_RELEASE)
			{
				switch (input.key)
				{
				case GLFW_KEY_RIGHT:
					inputVec.x = 0;
					break;
				case GLFW_KEY_LEFT:
					inputVec.x = 0;
					break;
				case GLFW_KEY_UP:
					inputVec.z = 0;
					break;
				case GLFW_KEY_DOWN:
					inputVec.z = 0;
					break;
				}
			}
		}
	};
}