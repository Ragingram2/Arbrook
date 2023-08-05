#pragma once
#include "core/core.hpp"
#include "rendering/rendering.hpp"

namespace rythe::game
{
	class Game : public core::System<core::transform, gfx::mesh_renderer>
	{
	private:
		core::ecs::entity camera;
		core::ecs::entity ent;
	public:
		void setup()
		{
			ent = createEntity("Cube");
			auto& transf = ent.addComponent<core::transform>();
			ent.addComponent<gfx::mesh_renderer>();

			transf.position = math::vec3(0, 0, -5.f);
			//camera = createEntity();
			//auto& transf = camera.addComponent<core::transform>();
			//transf.position = math::vec3(1.0);
			//camera.addComponent<gfx::camera>();
		}
	};
}