#pragma once
#include <rsl/primitives>
#include <rsl/utilities>

#include "core/logging/logging.hpp"

#include "rendering/interface/definitions.hpp"
#include "rendering/cache/shadercache.hpp"
#include "rendering/cache/texturecache.hpp"
#include "rendering/cache/buffercache.hpp"
#include "rendering/pipeline/base/pipelinebase.hpp"
#include "rendering/pipeline/base/graphicsstagebase.hpp"
#include "rendering/components/components.hpp"

namespace rythe::rendering
{
	template<typename Self, typename... componentTypes>
	struct graphics_stage : public graphics_stage_base, protected core::System<componentTypes...>
	{
		void shutdown_impl() override
		{
			if constexpr (has_shutdown_v<Self, void()>)
			{
				static_cast<Self*>(this)->shutdown();
			}
		}
	};

	//template<typename T>
	//concept StageType = std::derived_from<T, graphics_stage<T>;
}