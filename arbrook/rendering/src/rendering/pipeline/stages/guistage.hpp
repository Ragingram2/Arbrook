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
	using guiRenderFunc = void();
	struct gui_stage : public graphics_stage<gui_stage>
	{
	private:
		static rsl::multicast_delegate<guiRenderFunc> m_onGuiRender;
	public:
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

			m_onGuiRender();

			ImGui::Render();
			auto* draw_data = ImGui::GetDrawData();
			ImGui_ImplOpenGL3_RenderDrawData(draw_data);

			ImGui::EndFrame();
		}

		virtual rsl::priority_type priority() override { return UI_PRIORITY; }

		template <class T, void(T::* Func)()>
		static void addGuiRender(T* ptr)
		{
			m_onGuiRender.push_back<T,Func>(*ptr);
		}
	};

	inline rsl::multicast_delegate<guiRenderFunc> gui_stage::m_onGuiRender;
}