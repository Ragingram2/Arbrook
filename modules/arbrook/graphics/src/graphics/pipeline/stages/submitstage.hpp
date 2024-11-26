#pragma once
#include "core/assets/assethandle.hpp"
#include "core/components/transform.hpp"
#include "graphics/pipeline/base/graphicsstage.hpp"
#include "graphics/components/components.hpp"
#include "graphics/cache/shadercache.hpp"
#include "graphics/cache/modelcache.hpp"

namespace ast = rythe::core::assets;
namespace rythe::rendering
{
	struct submit_stage : public graphics_stage<submit_stage, core::transform>
	{
		framebuffer* mainFBO;
		virtual void setup(core::transform camTransf, camera& cam) override;
		virtual void render(core::transform camTransf, camera& cam) override;
		virtual rsl::priority_type priority() const override;
	};
}
