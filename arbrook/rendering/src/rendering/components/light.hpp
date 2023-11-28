#pragma once
#include <rsl/math>
#include <rsl/primitives>

namespace rythe::rendering
{
	enum struct LightType : rsl::uint
	{
		DIRECTIONAL = 0,
		POINT = 1,
		SPOT = 2
	};

	struct light_data
	{
		math::vec4 direction;
		math::vec4 position;
		math::vec4 color;
		float range = 50.0f;
		float intensity = 1.0f;
	};
	
	struct light
	{
		LightType type;
		rsl::uint index;
		light_data data;
		//union
		//{
		//	light_data data;
		//	struct
		//	{
		//		math::vec4 direction;
		//		math::vec4 position;
		//		math::vec4 color;
		//		float constant;
		//		float linear;
		//		float quadratic;
		//	};
		//};
	};

}