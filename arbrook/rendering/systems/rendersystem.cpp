#include "rendering/systems/rendersystem.hpp"

namespace rythe::rendering
{
	void Renderer::setup()
	{
		log::info("Initializing Render System");
		if (!glfwInit())
			return;

		auto wId = registry->m_worldId;
		m_api = &registry->m_entities[wId].addComponent<RenderInterface>();

		m_api->initialize(math::ivec2(600, 600), "Arbrook");

		if (!m_api->getWindow())
		{
			glfwTerminate();
			log::error("Window initialization failed");
			return;
		}
	}

	void Renderer::update()
	{
		m_api->makeCurrent();

		m_api->setSwapInterval(1);

		if (m_api->shouldWindowClose())
		{
			rythe::core::events::exit evnt(0);
			raiseEvent(evnt);
			return;
		}

		m_api->clear(GL_COLOR_BUFFER_BIT);
		m_api->setClearColor(0x64 / 255.0f, 0x95 / 255.0f, 0xED / 255.0f, 1.0f);

		for (auto& ent : m_filter)
		{
			auto& renderComp = ent.getComponent<sprite_renderer>();
			auto& transf = ent.getComponent<core::transform>();
			auto& example = ent.getComponent<core::exampleComp>();

			auto& shader = renderComp.m_shader;
			auto& texture = renderComp.m_texture;
			m_api->bind(shader);
			m_api->bind(texture);
			renderComp.vao.bind(m_api->getHwnd());

			shader->setUniform("u_position", transf.position);
			shader->setUniform("u_time", example.time);

			m_api->drawIndexed(PrimitiveType::TRIANGLESLIST, 6, DataType::UINT, nullptr);

			renderComp.vao.unbind();
		}

		m_api->swapBuffers();
		m_api->pollEvents();

		m_api->checkError();
	}

	void Renderer::shutdown()
	{
		glfwTerminate();
		m_api->close();
	}
}