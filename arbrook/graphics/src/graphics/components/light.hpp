#pragma once
#include <rsl/math>
#include <rsl/primitives>
#include <rfl.hpp>
#include <rfl/json.hpp>
#include <rfl/Variant.hpp>
#include <array>

namespace rythe::rendering
{
	enum struct LightType : rsl::uint
	{
		DIRECTIONAL = 0,
		POINT = 1,
		SPOT = 2
	};

	struct point_light_data
	{
		rfl::Skip<math::mat4> shadowProjection = math::mat4(0.0f);
		rfl::Skip<std::array<math::mat4, 6>> shadowTransforms;
		rfl::Skip<math::vec4> position = math::vec4(0.0f);
		math::vec4 color = math::vec4(0.0f);
		float intensity = 0.0f;
		float range = 0.0f;
		float farPlane = 0.0f;
	};

	struct dir_light_data
	{
		rfl::Skip<math::mat4> lightProjection = math::mat4(0.0f);
		rfl::Skip<math::mat4> lightView = math::mat4(0.0f);
		rfl::Skip<math::vec4> direction = math::vec4(0.0f);
		math::vec4 color = math::vec4(0.0f);
		float intensity = 0.0f;
	};

	struct light
	{
		rfl::Skip<bool> enabled = true;
		rfl::Skip<LightType> type;
		rfl::Skip<int> index = -1;
		std::variant<std::monostate, point_light_data, dir_light_data> data;

		point_light_data& asPointLight()
		{
			if (data.index() == 0)
				data.emplace<point_light_data>();
			return std::get<point_light_data>(data);
		}

		dir_light_data& asDirectionalLight()
		{
			if (data.index() == 0)
				data.emplace<dir_light_data>();
			return std::get<dir_light_data>(data);
		}
	};

}