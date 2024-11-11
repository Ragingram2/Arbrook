#pragma once
#include "core/logging/logging.hpp"
#include "core/modules/module.hpp"
#include "systems/game/game.hpp"
#include "systems/game/guisystem.hpp"
#include "systems/game/examplesystem.hpp"
#include "systems/game/cameracontrols.hpp"

namespace rythe::core
{
	class TestModule : public Module
	{
	public:
		void setup() override
		{
			log::info("Initializing Game Module");
			reportSystem<game::Game>();
			reportSystem<game::ExampleSystem>();
			reportSystem<game::GUISystem>();
			//reportSystem<game::PhysicsSystem>();
			reportSystem<game::CameraControls>();
			//reportSystem<testing::TestSystem>();
		}
	};
}