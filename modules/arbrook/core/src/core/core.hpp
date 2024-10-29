#pragma once
#include <rsl/math> 
#include <rsl/utilities> 
#include <rfl.hpp>
#include <rfl/json.hpp>

#include "modules/module.hpp"
#include "systems/system.hpp"
#include "scheduler/scheduler.hpp"
#include "logging/loggingservice.hpp"
#include "ecs/ecs.hpp"
#include "containers/pointer.hpp"
#include "events/events.hpp"
#include "components/components.hpp"
#include "assets/assets.hpp"
#include "timeutil/timetutil.hpp"



namespace rythe::rendering
{
	namespace math = rsl::math;
	namespace log = rsl::log;
}

namespace rythe::core
{
	namespace gfx = rythe::rendering;
	namespace log = rsl::log;
	namespace math = rsl::math;
	struct examplecomp
	{
		rfl::Skip<bool> enabled = true;
		float pos = 0.0f;
		float range = 0.0f;
		float speed = 0.0f;
		float angularSpeed = 0.0f;
		math::vec3 direction = math::vec3::zero;
		math::vec3 axis = math::vec3::up;
		math::vec3 initPosition = math::vec3::zero;
	};

	namespace events
	{
		namespace log = rsl::log;
		namespace math = rsl::math;
	}
	namespace scheduling
	{
		namespace log = rsl::log;
		namespace math = rsl::math;
	}
}
