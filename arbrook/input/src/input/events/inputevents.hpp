#pragma once
#include <rsl/math>

#include "core/events/event.hpp"
#include "input/map/inputmap.hpp"

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

	struct key_input final : public event<key_input>
	{
		inputmap::method key;
		bool value;
		key_input(inputmap::method _key, bool _value) : key(_key), value(_value) {}
	};

	struct mouse_input final : public event<mouse_input>
	{
		math::vec2 position;
		math::vec2 lastPosition;
		math::vec2 positionDelta;
		mouse_input(math::vec2 pos, math::vec2 lastPos, math::vec2 posDelta) : position(pos), lastPosition(lastPos), positionDelta(posDelta) {}
	};
}