#pragma once
#include "core/core.hpp"
#include "rendering/rendering.hpp"

namespace rythe::game
{
	class Game : public core::System<core::transform, gfx::mesh_renderer>
	{
	private:
		core::ecs::entity ent;
	public:
		void setup()
		{
			ent = createEntity();
			ent.addComponent<core::transform>();
			ent.addComponent<gfx::mesh_renderer>();
		}
	};
}