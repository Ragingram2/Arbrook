#include "sandbox/systems/testsystem.hpp"
namespace rythe::core
{

	void TestSystem::setup()
	{
		log::info("Initializing Test System");
		//if (!glfwInit())
		//	return;

		auto wId = registry->m_worldId;
		m_api = &registry->m_entities[wId].addComponent<gfx::RenderInterface>();
		m_api->initialize(math::ivec2(Screen_Width, Screen_Height), "Arbrook");

		if (!m_api->getWindow())
		{
			//glfwTerminate();
			log::error("Window initialization failed");
			return;
		}
		vertex verticies[] =
		{	//positions						
			{{  -1.f, 1.f, 0.0f  },{0,1}},//0
			{{ 	-1.f,-1.f, 0.0f  },{0,0}},//1
			{{  1.f,-1.f, 0.0f  },{1,0}},//2
			{{  -1.f, 1.f, 0.0f  },{0,1}},//0
			{{  1.f,-1.f, 0.0f },{1,0}},//2
			{{  1.f, 1.f, 0.0f },{1,1}}//3
		};



		shader = gfx::ShaderCache::createShader(*m_api, "test", "resources/shaders/fluid.shader");
		vertexHandle = gfx::BufferCache::createBuffer<vertex>(*m_api, "Vertex Buffer", gfx::TargetType::VERTEX_BUFFER, gfx::UsageType::STATICDRAW, verticies, sizeof(verticies) / sizeof(vertex));
		constantHandle = gfx::BufferCache::createBuffer<math::vec4>(*m_api, "ConstantBuffer", gfx::TargetType::CONSTANT_BUFFER, gfx::UsageType::STATICDRAW);
		shader->addBuffer(gfx::ShaderType::FRAGMENT, constantHandle);
		shader->bind();

		layout.initialize(m_api->getHwnd(), 1, shader);
		vertexHandle->bind();
		layout.setAttributePtr("POSITION", 0, gfx::FormatType::RGB32F, 0, sizeof(vertex), 0);
		layout.setAttributePtr("TEXCOORD", 1, gfx::FormatType::RG32F, 0, sizeof(vertex), sizeof(math::vec3));
		layout.bind();

		for (int x = 0; x < SIZE; x++)
		{
			for (int y = 0; y < SIZE; y++)
			{
				addDensity(x, y, .5f);
			}
		}

	}

	void TestSystem::update()
	{
		m_api->makeCurrent();
		m_api->setSwapInterval(0);

		if (m_api->shouldWindowClose())
		{
			rythe::core::events::exit evnt(0);
			raiseEvent(evnt);
			return;
		}

		m_api->setViewport(1, 0, 0, Screen_Width, Screen_Height, 0, 1);
		m_api->setClearColor(0x64 / 255.0f, 0x95 / 255.0f, 0xED / 255.0f, 1.0f);
		m_api->clear(gfx::ClearBit::COLOR);


		//int N = SIZE;

		//addDensity((SIZE / 2), (SIZE / 2), 10.f);
		//addVelocity(SIZE / 2, SIZE / 2, 0.f, 1.f);
		//step(5, .002f);
		//log::debug(cube.source[IX((SIZE / 2)-1, SIZE / 2)]);
		render();

		m_api->swapBuffers();
		m_api->pollEvents();
	}

	void TestSystem::shutdown()
	{
		log::info("Shutting down Test System ");
	}

	void TestSystem::render()
	{
		shader->setData("ConstantBuffer", cube.density);
		m_api->drawArrays(gfx::PrimitiveType::TRIANGLESLIST, 0, 6);
	}
}