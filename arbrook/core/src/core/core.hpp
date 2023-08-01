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

	namespace events
	{
		namespace log = rsl::log;
	}
	namespace scheduling
	{
		namespace log = rsl::log;
	}
}
