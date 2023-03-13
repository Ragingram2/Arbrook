#include "rendering/systems/rendersystem.hpp"

namespace rythe::rendering
{
	void Renderer::setup()
	{
		log::info("Initializing Render System");
		if (!glfwInit())
			return;

		m_renderApi.initialize(m_window, math::ivec2(600, 600), "Arbrook");

		if (!m_window.getWindow())
		{
			glfwTerminate();
			log::error("Window initialization failed");
			return;
		}
	}

	void Renderer::update()
	{
		window::makeCurrent();

		m_window.setSwapInterval(1);

		if (m_window.shouldClose())
		{
			rythe::core::events::exit evnt(0);
			raiseEvent(evnt);
			return;
		}

		m_renderApi.clear(GL_COLOR_BUFFER_BIT);
		m_renderApi.setClearColor(0x64 / 255.0f, 0x95 / 255.0f, 0xED / 255.0f, 1.0f);

		for (auto& ent : m_filter)
		{
			auto& renderComp = ent.getComponent<sprite_renderer>();
			auto& transf = ent.getComponent<core::transform>();
			auto& example = ent.getComponent<core::exampleComp>();

			auto& shader = renderComp.m_shader;
			auto& texture = renderComp.m_texture;
			m_renderApi.bind(shader);
			m_renderApi.bind(texture);
			renderComp.vao->bind();

			m_renderApi.setUniform(shader, "u_position", transf.position);
			m_renderApi.setUniform(shader, "u_time", example.time);

			m_renderApi.drawIndexed(DrawMode::TRIANGLES, 6, DataType::UINT, nullptr);

			renderComp.vao->unbind();
		}

		m_window.swapBuffers();
		m_window.pollEvents();
	}

	void Renderer::shutdown()
	{
		glfwTerminate();
	}
}