#pragma once
#include "core/systems/system.hpp"
#include "core/logging/logging.hpp"

namespace rythe::core
{
	class TestSystem : public System<transform, renderComp, exampleComp>
	{
	public:
		TestSystem() = default;
		virtual ~TestSystem() = default;

		void setup() override;
		void update() override;
		void shutdown() override;
	};
}