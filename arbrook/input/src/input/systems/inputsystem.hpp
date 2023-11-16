#pragma once
#include <gainput/gainput.h>

#include "core/systems/system.hpp"
#include "input/map/inputmap.hpp"
#include "input/events/inputevents.hpp"

namespace rythe::input
{
	//Figure out what to do here
	class InputSystem : public core::System<InputSystem>
	{
	private:
		static HWND m_windowHandle;
	public:
		InputSystem() = default;
		virtual ~InputSystem() = default;
		void setup();
		void update();
		void shutdown();

		static void registerWindow(void* windowHandle);
	};
}