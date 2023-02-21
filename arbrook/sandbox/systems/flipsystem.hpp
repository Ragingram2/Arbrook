#pragma once
#include "core/systems/system.hpp"
#include "core/logging/logging.hpp"

namespace rythe::core
{
	class FlipSystem : public System<transform, rigidbody>
	{
	public:
		FlipSystem() = default;
		virtual ~FlipSystem() = default;

		void setup() override;
		void update() override;
		void shutdown() override;

		int m_cellSize = 3;
		float density = 1;
		math::ivec2 m_resolution = math::ivec2(720, 640);
		math::vec2 m_gravity = math::vec2(0.0f, 9.8f);
	};
}
