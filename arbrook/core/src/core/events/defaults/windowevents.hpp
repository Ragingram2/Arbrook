#pragma once
#include "core/events/event.hpp"

namespace rythe::core::events
{
	struct window_created final : public event<window_created>
	{
		unsigned int size;
		void* hwnd;

		window_created(unsigned int size, void* hwnd) : size(size), hwnd(hwnd) {}
	};
}