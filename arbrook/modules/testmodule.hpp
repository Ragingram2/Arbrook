#pragma once
#include "logging/logging.hpp"
#include "modules/module.hpp"

namespace rythe::core
{
	class TestModule : public Module
	{
	public:
		void initialize() override;
		void update() override { Module::update(); };
		void shutdown() override { Module::shutdown(); };
	};
}