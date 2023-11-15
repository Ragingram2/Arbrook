#pragma once
#include "core/events/event.hpp"
#include "core/input/inputmap.hpp"

namespace rythe::core::events
{
	using namespace input;
	template<typename eventType>
	struct input_action : public event<eventType>
	{
		bool value;
		float input_delta;
		inputmap::modifier_keys mods;
		inputmap::method id;

		void set(bool _value, inputmap::modifier_keys _mods, inputmap::method _id)
		{
			value = _value;
			mods = _mods;
			id = _id;
		}

		bool pressed() const { return value; }
		bool released() const { return !value; }
	};

	template<typename eventType>
	struct input_axis : public event<eventType>
	{
		float value;
		float input_delta;
		std::vector<float> value_parts;
		inputmap::modifier_keys mods;
		inputmap::method identifier;
		std::vector<inputmap::modifier_keys> mods_parts;
		std::vector<inputmap::method> identifier_parts;
	};
}