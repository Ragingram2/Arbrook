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

	public:
		void setup();

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
	};
}