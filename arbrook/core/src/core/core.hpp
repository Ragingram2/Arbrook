#pragma once
#include <rsl/utilities>
#include <rsl/math>

#include "core/modules/module.hpp"
#include "core/systems/system.hpp"
#include "core/scheduler/scheduler.hpp"
#include "core/logging/loggingservice.hpp"
#include "core/ecs/ecs.hpp"
#include "core/containers/pointer.hpp"
#include "core/events/events.hpp"
#include "core/components/components.hpp"
#include "core/assets/assets.hpp"
#include "core/timeutil/timetutil.hpp"


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
		float pos = 0.0f;
		float range = 0.0f;
		float speed = 0.0f;
		float angularSpeed = 0.0f;
		math::vec3 direction = math::vec3::zero;
		math::vec3 axis = math::vec3::up;
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
