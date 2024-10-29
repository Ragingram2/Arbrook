#include "guistage.hpp"
namespace rythe::rendering
{
	namespace log = rsl::log;
	using guiRenderFunc = void(core::transform, camera);

	rsl::multicast_delegate<guiRenderFunc> gui_stage::m_onGuiRender;
	framebuffer* mainFBO;
	void gui_stage::setup(core::transform camTransf, camera& cam)
	{
		mainFBO = getFramebuffer("MainBuffer");
		RI->makeCurrent();
		auto* ctx = ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ctx->IO.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		//ctx->IO.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		ImGui::SetCurrentContext(ctx);
#if RenderingAPI == RenderingAPI_OGL
		if (!ImGui_ImplGlfw_InitForOpenGL(RI->getGlfwWindow(), true))
		{
			log::error("Imgui GLFW initialization failed");
		}
		if (!ImGui_ImplOpenGL3_Init("#version 420"))
		{
			log::error("Imgui OpenGL initialization failed");
		}
#elif RenderingAPI == RenderingAPI_DX11
		if (!ImGui_ImplGlfw_InitForOther(RI->getGlfwWindow(), true))
		{
			log::error("Imgui GLFW initialization failed");
		}
		if (!ImGui_ImplDX11_Init(RI->getWindowHandle()->dev.Get(), RI->getWindowHandle()->devcon.Get()))
		{
			log::error("Imgui DX11 initialization failed");
		}
#elif RenderingAPI == RenderingAPI_VK
		ImGui_ImplVulkan_LoadFunctions();
		if (!ImGui_ImplGlfw_InitForVulkan(RI->getGlfwWindow(), true))
		{
			log::error("Imgui GLFW initialization failed");
		}
		if (!ImGui_ImplVulkan_Init(RI->getWindowHandle()->dev.Get(), RI->getWindowHandle()->devcon.Get()))
		{
			log::error("Imgui Vulkan initialization failed");
		}
#endif
	}

	void gui_stage::render(core::transform camTransf, camera& cam)
	{
		ZoneScopedN("[Renderer] GUI Stage");
#if RenderingAPI == RenderingAPI_OGL
		ImGui_ImplOpenGL3_NewFrame();
#elif RenderingAPI == RenderingAPI_DX11
		ImGui_ImplDX11_NewFrame();
#elif RenderingAPI == RenderingAPI_VK
		ImGui_ImplVulkan_NewFrame();
#endif
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGuizmo::BeginFrame();
		m_onGuiRender(camTransf, cam);
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
		ImGui::EndFrame();
		ImGui::Render();
		auto* draw_data = ImGui::GetDrawData();

#if RenderingAPI == RenderingAPI_OGL
		ImGui_ImplOpenGL3_RenderDrawData(draw_data);
#elif RenderingAPI == RenderingAPI_DX11
		//mainFBO->getAttachment(AttachmentSlot::COLOR0)->unbind(TextureSlot::TEXTURE0);
		mainFBO->unbind();
		WindowProvider::activeWindow->checkError();
		ImGui_ImplDX11_RenderDrawData(draw_data);
		WindowProvider::activeWindow->checkError();
#elif RenderingAPI == RenderingAPI_VK
		ImGui_ImplVulkan_RenderDrawData(draw_data);
#endif
		RI->swapBuffers();
	}

	rsl::priority_type gui_stage::priority() const { return UI_PRIORITY; }
}