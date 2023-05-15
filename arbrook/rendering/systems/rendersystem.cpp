#include "rendering/systems/rendersystem.hpp"
#include <GLFW/glfw3.h>
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

		//glfwSetKeyCallback(m_api->getWindow(), key_callback);

		//testEnt = createEntity("Test");
		//testEnt.addComponent<core::transform>();
		//auto& renderer = testEnt.addComponent<sprite_renderer>();
		//auto& layout = renderer.layout;
		//auto vertexHandle = BufferCache::createBuffer<vertex>(*m_api, "Vertex Buffer", TargetType::VERTEX_BUFFER);
		//auto indexHandle = BufferCache::createBuffer<unsigned int>(*m_api, "Index Buffer", TargetType::INDEX_BUFFER);
		//auto texture = TextureCache::createTexture2D(*m_api, "Rythe", "resources/textures/Rythe.png");
		//auto constantHandle = BufferCache::createBuffer<vtx_constant>(*m_api, "ConstantBuffer", TargetType::CONSTANT_BUFFER);
		//auto shader = ShaderCache::createShader(*m_api, "color", "resources/shaders/color.shader");
		//auto defShader = ShaderCache::createShader(*m_api, "default", "resources/shaders/default.shader");
		//layout.addBuffer(indexHandle);
		//layout.addBuffer(vertexHandle);
		//layout.bind(m_api->getHwnd(), shader);
		//layout.setAttributePtr("POSITION", 0, FormatType::RGB32F, sizeof(vertex), 0, InputClass::PER_VERTEX, 0);
		//layout.setAttributePtr("COLOR", 1, FormatType::RGBA32F, sizeof(vertex), 3.0f * sizeof(float), InputClass::PER_VERTEX, 0);
		//layout.setAttributePtr("TEXCOORD", 2, FormatType::RG32F, sizeof(vertex), 7.0f * sizeof(float), InputClass::PER_VERTEX, 0);
		//layout.submitAttributes();

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

		m_api->setViewport(1, 0, 0, 600, 600, 0, 1);
		m_api->setClearColor(0x64 / 255.0f, 0x95 / 255.0f, 0xED / 255.0f, 1.0f);

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