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

		auto constantHandle = BufferCache::getBuffer("Constant Buffer");

		int i = 0;
		for (auto& ent : m_filter)
		{
			auto& renderComp = ent.getComponent<sprite_renderer>();
			auto& transf = ent.getComponent<core::transform>();
			auto& example = ent.getComponent<core::exampleComp>();

			auto& shader = renderComp.shader;
			auto& texture = renderComp.texture;

			vtx_constant constant[] = { { transf.position,example.time } };
			constantHandle->bufferData<vtx_constant, float>(constant, 1);

			shader->bind();
			//m_api->bind(texture);
			renderComp.layout.bind(m_api->getHwnd(), shader);

			//shader->setUniform("u_position", transf.position);
			//shader->setUniform("u_time", example.time);

			m_api->drawIndexed(PrimitiveType::TRIANGLESTRIP, 6, 0, 0);
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