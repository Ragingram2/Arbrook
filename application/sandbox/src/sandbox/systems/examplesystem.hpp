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
				comp.i += comp.speed;

				auto& transf = ent.getComponent<core::transform>();
				transf.position = math::vec3(math::sin(math::radians(comp.i)) * comp.range * comp.direction, transf.position.y, transf.position.z);
				//transf.rotation = math::toQuat(math::rotate(transf.to_parent(), math::radians(comp.i) * comp.direction, transf.up()));
			}
		}
	};
}
