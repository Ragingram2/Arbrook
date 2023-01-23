#pragma once
#include "systems/system.hpp"

namespace rythe::core
{
	class TestSystem : public System
	{
	public:
		TestSystem() = default;
		virtual ~TestSystem() = default;

		void setup() override;
		void update() override;
		void shutdown() override;
	};
}