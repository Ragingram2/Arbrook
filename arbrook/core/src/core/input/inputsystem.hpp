#pragma once
#include "core/input/inputmap.hpp"
#include "core/events/defaults/inputevents.hpp"
#include "core/systems/system.hpp"

namespace rythe::core::input
{
	//Figure out what to do here
	class InputSystem : public core::System<InputSystem>
	{
	public:
		void setup();
	};
}