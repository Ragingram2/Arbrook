#pragma once
#include "logging/logging.hpp"
#include "modules/module.hpp"
#include "systems/testsystem.hpp"

namespace rythe::core
{
	class TestModule : public Module
	{
	public:
		void setup() override;
		//void update() override;
		//void shutdown() override;
	};
}