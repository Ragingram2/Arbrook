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

	struct key_input final : public event<key_input>
	{
		int key;
		int scancode;
		int action;
		int mods;
		key_input(int key, int scancode, int action, int mods) : key(key), scancode(scancode), action(action), mods(mods) {}
	};
}