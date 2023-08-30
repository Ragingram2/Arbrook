#pragma once
#include <imgui/imgui.h> 
#include <imgui/imgui_internal.h>

#include <rsl/primitives>
#include <rsl/utilities>

#include "core/logging/logging.hpp"
#include "core/components/transform.hpp"
#include "rendering/cache/cache.hpp"
#include "rendering/interface/definitions.hpp"
#include "rendering/pipeline/base/graphicsstage.hpp"
#include "rendering/components/mesh_renderer.hpp"
#include "rendering/components/camera.hpp"

namespace rythe::rendering
{
	struct gui_stage : public graphics_stage<gui_stage>
	{
		virtual void setup(core::transform camTransf, camera& cam) override
		{
			RI->makeCurrent();
			auto* ctx = ImGui::CreateContext();
			ImGui::StyleColorsDark();
			ImGui::SetCurrentContext(ctx);
			ImGui_ImplGlfw_InitForOpenGL(RI->getWindow(),true);
			ImGui_ImplOpenGL3_Init("#version 420");
		}

		virtual void render(core::transform camTransf, camera& cam) override
		{
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			ImGui::ShowDemoWindow();

			ImGui::Render();
			auto* draw_data = ImGui::GetDrawData();
			ImGui_ImplOpenGL3_RenderDrawData(draw_data);
		}

		virtual rsl::priority_type priority() override { return UI_PRIORITY; }
	};
}