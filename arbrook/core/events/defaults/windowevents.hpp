#pragma once
#include "core/events/event.hpp"

namespace rythe::core::events
{
	struct key_input final : public event<key_input>
	{
		int key;
		int scancode;
		int action;
		int mods;
		key_input(int key, int scancode, int action, int mods) : key(key), scancode(scancode), action(action), mods(mods) {}
	};
}