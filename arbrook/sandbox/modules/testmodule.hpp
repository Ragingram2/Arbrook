#pragma once
#include "core/logging/logging.hpp"
#include "core/modules/module.hpp"
#include "sandbox/systems/testsystem.hpp"
#include "sandbox/systems/flipsystem.hpp"

namespace rythe::core
{
	class TestModule : public Module
	{
	public:
		void setup() override;
	};
}