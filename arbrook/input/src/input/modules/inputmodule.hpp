#pragma once
#include "core/modules/module.hpp"
#include "core/logging/logging.hpp"
#include "input/systems/inputsystem.hpp"

namespace rythe::input
{
	class InputModule : public core::Module
	{
	public:
		void setup() 
		{
			log::info("Initializing Input Module");
			reportSystem<InputSystem>();
		}

	};
}