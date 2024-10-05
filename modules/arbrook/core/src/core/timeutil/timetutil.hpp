#pragma once

namespace rythe::core
{
	struct Time
	{
		static float previousDeltaTime;
		static float deltaTime;
	};

	inline float Time::deltaTime;
	inline float Time::previousDeltaTime;
}