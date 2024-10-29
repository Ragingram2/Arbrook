#pragma once
#include <rsl/primitives>
#include <rsl/utilities>
#include <rsl/math>
#include <rsl/logging>

#include "core/events/defaults/component_event.hpp"
#include "core/components/transform.hpp"
#include "core/assets/assethandle.hpp"
#include "../cache/cache.hpp"
#include "../data/shaderhandle.hpp"
#include "../components/components.hpp"
#include "../pipeline/base/graphicsstage.hpp"
#include "../interface/definitions/definitions.hpp"

namespace rythe::rendering
{
	struct shadow_map_stage : public graphics_stage<shadow_map_stage, mesh_renderer, core::transform>
	{
		framebuffer* depthCubeFBO;
		framebuffer* depthFBO;
		framebuffer* mainFBO;
		shader_handle pointShadowMap;
		shader_handle dirShadowMap;

		buffer_handle cameraBuffer;
		buffer_handle materialBuffer;
		buffer_handle pointLightBuffer;
		buffer_handle directionalLightBuffer;
		buffer_handle lightInfoBuffer;

		virtual void setup(core::transform camTransf, camera& cam) override;

		virtual void render(core::transform camTransf, camera& cam) override;

		virtual rsl::priority_type priority() const override;

		void directionalLightPass(core::transform& camTransf, camera& cam);

		void pointLightPass(core::transform& camTransf, camera& cam);

		void initializeModel(mesh_renderer& renderer, shader_handle handle);
	};
}