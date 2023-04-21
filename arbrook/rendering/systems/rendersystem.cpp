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

		//We can't do this here because no entities exist during rendersystems setup. We need to make model and material abstractions
		auto vertexHandle = BufferCache::createBuffer<vertex>(*m_api, "Vertex Buffer", TargetType::VERTEX_BUFFER, UsageType::STATICDRAW);
		auto indexHandle = BufferCache::createBuffer<unsigned int>(*m_api, "Index Buffer", TargetType::INDEX_BUFFER, UsageType::STATICDRAW);
		auto constantHandle = BufferCache::createBuffer<vtx_constant>(*m_api, "Constant Buffer", TargetType::CONSTANT_BUFFER, UsageType::STATICDRAW, nullptr, 1);

		for (auto& ent : m_filter)
		{
			auto& renderComp = ent.getComponent<sprite_renderer>();
			vertexHandle->bufferData(renderComp.verticies, 4);
			indexHandle->bufferData(renderComp.indicies, 6);
			renderComp.layout.addBuffer(vertexHandle);
			renderComp.layout.addBuffer(indexHandle);

			renderComp.shader->addBuffer(ShaderType::VERTEX, constantHandle);
			renderComp.shader->bind();
			renderComp.texture->bind();

			renderComp.layout.bind(m_api->getHwnd(), renderComp.shader);
			renderComp.layout.setAttributePtr("POSITION", 0, FormatType::RGB32F, sizeof(vertex), 0);
			renderComp.layout.setAttributePtr("COLOR", 1, FormatType::RGBA32F, sizeof(vertex), 3.0f * sizeof(float));
			renderComp.layout.setAttributePtr("TEXCOORD", 2, FormatType::RG32F, sizeof(vertex), 7.0f * sizeof(float));
			renderComp.layout.submitAttributes();
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

			auto& shader = renderComp.shader;
			auto& texture = renderComp.texture;

			shader->bind();
			texture->bind();
			renderComp.layout.bind(m_api->getHwnd(), shader);

			vtx_constant constant[] = { { transf.position,example.time } };
			shader->setData("Constant Buffer", constant);

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