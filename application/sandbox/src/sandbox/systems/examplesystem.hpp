#pragma once
#include "core/core.hpp"

namespace rythe::game
{
	using namespace rythe::core::events;
	class ExampleSystem : public core::System<core::examplecomp>
	{
	public:
		void setup()
		{

		}
		void update()
		{
			for (auto ent : m_filter)
			{
				auto& comp = ent.getComponent<core::examplecomp>();
				comp.i += .1f;

				auto& transf = ent.getComponent<core::transform>();
				transf.position = math::vec3(math::sin(math::radians(comp.i)) * 5.0f * comp.direction, transf.position.y, transf.position.z);
			}
		}
	};
}
