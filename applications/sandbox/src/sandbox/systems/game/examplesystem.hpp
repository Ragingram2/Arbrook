#pragma once
#include "core/core.hpp"

namespace rythe::game
{
	using namespace rythe::core::events;
	class ExampleSystem : public core::System<ExampleSystem, core::examplecomp>
	{
	public:
		void setup()
		{
			for (auto ent : m_filter)
			{
				auto& comp = ent.getComponent<core::examplecomp>();
				auto& transf = ent.getComponent<core::transform>();
				comp.initPosition = transf.position;
			}
		}

		void update()
		{
			for (auto ent : m_filter)
			{
				auto& comp = ent.getComponent<core::examplecomp>();
				if (!ent->enabled || !comp.enabled.get()) continue;

				comp.pos += comp.speed * core::Time::deltaTime;

				auto& transf = ent.getComponent<core::transform>();
				transf.position = comp.initPosition + (comp.direction * math::sin(math::deg2rad(comp.pos)) * comp.range);

				if (math::length(comp.axis) > 0)
					transf.rotation = math::quat(math::rotate(transf.to_parent(), math::deg2rad(comp.angularSpeed * core::Time::deltaTime), comp.axis));
			}
		}
	};
}
