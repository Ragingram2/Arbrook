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

		auto colorShader = ShaderCache::getShader("color");
		m_api->clear(ClearBit::COLOR_DEPTH_STENCIL);
		m_api->setClearColor(0x64 / 255.0f, 0x95 / 255.0f, 0xED / 255.0f, 1.0f);

		for (auto& ent : m_filter)
		{
			auto& renderComp = ent.getComponent<sprite_renderer>();
			auto& transf = ent.getComponent<core::transform>();
			auto& example = ent.getComponent<core::exampleComp>();

			auto& shader = renderComp.shader;
			auto& texture = renderComp.texture;

			shader->bind();
			texture->bind();
			renderComp.layout.bind(m_api->getHwnd(), shader);

			vtx_constant constant[] = { { transf.position,example.time } };
			shader->setData("ConstantBuffer", constant);
			colorShader->setData("ConstantBuffer", constant);

			m_api->setDepthFunction(DepthFuncs::LESS_EQUAL);
			m_api->enableStencilTest();
			m_api->setStencilOp(Face::FRONT_BACK, StencilOp::KEEP, StencilOp::KEEP, StencilOp::REPLACE);

			m_api->setStencilFunction(Face::FRONT_BACK, DepthFuncs::ALWAYS, 1, 0xFF);
			m_api->enableDepthWrite();
			m_api->updateDepthStencil();
			m_api->drawIndexed(PrimitiveType::TRIANGLESTRIP, 4, 0, 0);

			m_api->setStencilFunction(Face::FRONT_BACK, DepthFuncs::NOT_EQUAL, 1, 0xFF);
			m_api->disableDepthWrite();
			m_api->disableDepthTest();
			m_api->updateDepthStencil();
			colorShader->bind();
			m_api->drawIndexed(PrimitiveType::TRIANGLESTRIP, 4, 0, 0);

			m_api->enableDepthWrite();
			m_api->setStencilFunction(Face::FRONT_BACK, DepthFuncs::ALWAYS, 1, 0xFF);
			m_api->enableDepthTest();
			m_api->updateDepthStencil();

			m_api->clear(ClearBit::STENCIL);
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