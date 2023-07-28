#pragma once

#include "core/modules/module.hpp"
#include "core/systems/system.hpp"
#include "core/scheduler/scheduler.hpp"
#include "core/logging/loggingservice.hpp"
#include "core/math/math.hpp"
#include "core/ecs/ecs.hpp"
#include "core/containers/pointer.hpp"
#include "core/events/events.hpp"
#include <rsl/utilities>

namespace rythe::rendering
{
	namespace math = core::math;
	namespace log = core::log;
}

namespace rythe::core
{
	namespace gfx = rythe::rendering;
}
