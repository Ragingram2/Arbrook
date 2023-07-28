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
#include "rendering/components/mesh_renderer.hpp"

namespace rythe::rendering
{
	template<typename Self>
	struct graphics_stage : public graphics_stage_base, protected core::System<mesh_renderer>
	{
		void shutdown_impl() override
		{
		}
	};

	template<typename T>
	concept StageType = std::derived_from<T, graphics_stage<T>>;
}