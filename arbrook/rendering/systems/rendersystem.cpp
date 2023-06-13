#include "rendering/systems/rendersystem.hpp"
#include <GLFW/glfw3.h>
namespace rythe::rendering
{
	//a fucntion that will generate vertex buffers with given paramters
	std::vector<std::unique_ptr<rendering_test>> Renderer::m_testScenes;
	int Renderer::currentScene = 0;
	int Renderer::lastScene = 0;
	bool Renderer::initializeTest = true;
	bool Renderer::updateTest = false;
	bool Renderer::stopTest = false;

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

		glfwSetKeyCallback(m_api->getWindow(), key_callback);

		//BufferCache::createBuffer<vertex>(*m_api, "Vertex Buffer", TargetType::VERTEX_BUFFER);
		//BufferCache::createBuffer<unsigned int>(*m_api, "Index Buffer", TargetType::INDEX_BUFFER);
		//TextureCache::createTexture2D(*m_api, "Rythe", "resources/textures/Rythe.png");
		//BufferCache::createBuffer<vtx_constant>(*m_api, "ConstantBuffer", TargetType::CONSTANT_BUFFER);

#pragma region Abstracted API

		//DrawArrays
		m_testScenes.emplace_back(std::make_unique<dummy_test>());
		m_testScenes.emplace_back(std::make_unique<API_DrawArraysTest>());
		m_testScenes.emplace_back(std::make_unique<Native_DrawArraysTest>());
		//m_testScenes.emplace_back(std::make_unique<BGFX_DrawArraysTest>());

		//DrawArraysInstanced
		m_testScenes.emplace_back(std::make_unique<API_DrawArraysInstancedTest>());
		m_testScenes.emplace_back(std::make_unique<Native_DrawArraysInstancedTest>());

		//DrawIndexed
		m_testScenes.emplace_back(std::make_unique<API_DrawIndexedTest>());
		m_testScenes.emplace_back(std::make_unique<Native_DrawIndexedTest>());

		//DrawIndexedInstanced
		m_testScenes.emplace_back(std::make_unique<API_DrawIndexedInstancedTest>());
		m_testScenes.emplace_back(std::make_unique<Native_DrawIndexedInstancedTest>());

		////TestSetViewport
		////m_testScenes.emplace_back(rendering_test
		////	{
		////		[](inputlayout* layout, RenderInterface* api)
		////			{
		////				log::debug("Initializing TestSetViewport");
		////				glfwSetWindowTitle(api->getWindow(), "TestSetViewport");
		////			},
		////		[](inputlayout* layout, RenderInterface* api)
		////			{
		////				api->setViewport(1, 300, 300, 600, 600, 0, 1);
		////				api->setClearColor(.5f, .5f, .5f, 1.0f);
		////				api->clear(ClearBit::COLOR);
		////			},
		////		[](inputlayout* layout, RenderInterface* api) { }
		////	});

		////TestStencilTest
		//m_testScenes.emplace_back(rendering_test
		//	{
		//		[](inputlayout* layout, RenderInterface* api)
		//			{
		//				log::debug("Initializing TestStencilTest");
		//				glfwSetWindowTitle(api->getWindow(), "TestStencilTest");
		//				math::vec3 verticies[6] =
		//				{	//positions					//colors	
		//					{  -0.1f, 0.1f, 0.0f },//0
		//					{ 	-0.1f,-0.1f, 0.0f },//1
		//					{  0.1f,-0.1f, 0.0f },//2
		//					{  -0.1f, 0.1f, 0.0f },//0
		//					{  0.1f,-0.1f, 0.0f },//2
		//					{  0.1f, 0.1f, 0.0f }//3
		//				};

		//				auto vertexHandle = BufferCache::createBuffer<math::vec3>(*api, "Vertex Buffer", TargetType::VERTEX_BUFFER, UsageType::STATICDRAW, verticies, sizeof(verticies) / sizeof(math::vec3));
		//				auto shader1Handle = ShaderCache::createShader(*api, "color", "resources/shaders/color.shader");
		//				ShaderCache::createShader(*api, "scaled_color", "resources/shaders/scaled_color.shader");
		//				shader1Handle->bind();
		//				layout->addBuffer(vertexHandle);
		//				layout->bind(api->getHwnd(), shader1Handle);
		//				layout->setAttributePtr("POSITION", 0, FormatType::RGB32F, 0, sizeof(math::vec3), 0);
		//				layout->submitAttributes();
		//				api->depthTest(true);
		//				api->setDepthFunction(DepthFuncs::LESS);
		//				api->stencilTest(true);
		//				api->setStencilFunction(Face::FRONT,DepthFuncs::NOT_EQUAL,1,0xFF);
		//				api->setStencilOp(Face::FRONT,StencilOp::KEEP,StencilOp::KEEP,StencilOp::REPLACE);
		//			},
		//		[](inputlayout* layout, RenderInterface* api)
		//			{
		//				auto shader1Handle = ShaderCache::getShader("color");
		//				shader1Handle->bind();
		//				layout->bind(api->getHwnd(), shader1Handle);
		//				api->clear(ClearBit::COLOR_DEPTH_STENCIL);

		//				api->setStencilFunction(Face::FRONT, DepthFuncs::ALWAYS, 1, 0xFF);
		//				api->setStencilMask(0xFF);
		//				api->updateDepthStencil();
		//				api->drawArrays(PrimitiveType::TRIANGLESLIST, 0, 6);

		//				auto shader2Handle = ShaderCache::getShader("scaled_color");
		//				shader2Handle->bind();
		//				api->setStencilFunction(Face::FRONT, DepthFuncs::NOT_EQUAL, 1, 0xFF);
		//				api->setStencilMask(0x00);
		//				api->depthTest(false);
		//				api->updateDepthStencil();
		//				api->drawArrays(PrimitiveType::TRIANGLESLIST, 0, 6);

		//				api->setStencilMask(0xFF);
		//				api->setStencilFunction(Face::FRONT, DepthFuncs::ALWAYS, 0, 0xFF);
		//				api->depthTest(true);
		//				api->updateDepthStencil();
		//			},
		//		[](inputlayout* layout, RenderInterface* api)
		//			{
		//				BufferCache::deleteBuffer("Vertex Buffer");
		//				ShaderCache::deleteShader("color");
		//				ShaderCache::deleteShader("scaled_color");
		//				layout->release();

		//				api->depthTest(false);
		//				api->stencilTest(false);
		//				api->updateDepthStencil();
		//			}
		//	});

#pragma endregion

#pragma region Bare API

		//		//TestStencilTest
		//		m_testScenes.emplace_back(rendering_test
		//			{
		//				[](inputlayout* layout, RenderInterface* api)
		//					{
		//						log::debug("Initializing TestStencilTest");
		//						glfwSetWindowTitle(api->getWindow(), "TestStencilTest");
		//						math::vec3 verticies[6] =
		//						{	//positions					//colors	
		//							{  -0.1f, 0.1f, 0.0f },//0
		//							{ 	-0.1f,-0.1f, 0.0f },//1
		//							{  0.1f,-0.1f, 0.0f },//2
		//							{  -0.1f, 0.1f, 0.0f },//0
		//							{  0.1f,-0.1f, 0.0f },//2
		//							{  0.1f, 0.1f, 0.0f }//3
		//						};
		//
		//						auto vertexHandle = BufferCache::createBuffer<math::vec3>(*api, "Vertex Buffer", TargetType::VERTEX_BUFFER, UsageType::STATICDRAW, verticies, sizeof(verticies) / sizeof(math::vec3));
		//						auto shader1Handle = ShaderCache::createShader(*api, "color", "resources/shaders/color.shader");
		//						ShaderCache::createShader(*api, "scaled_color", "resources/shaders/scaled_color.shader");
		//						shader1Handle->bind();
		//						layout->addBuffer(vertexHandle);
		//						layout->bind(api->getHwnd(), shader1Handle);
		//						layout->setAttributePtr("POSITION", 0, FormatType::RGB32F, 0, sizeof(math::vec3), 0);
		//						layout->submitAttributes();
		//						api->depthTest(true);
		//						api->setDepthFunction(DepthFuncs::LESS);
		//						api->stencilTest(true);
		//						api->setStencilFunction(Face::FRONT,DepthFuncs::NOT_EQUAL,1,0xFF);
		//						api->setStencilOp(Face::FRONT,StencilOp::KEEP,StencilOp::KEEP,StencilOp::REPLACE);
		//					},
		//				[](inputlayout* layout, RenderInterface* api)
		//					{
		//						auto shader1Handle = ShaderCache::getShader("color");
		//						shader1Handle->bind();
		//						layout->bind(api->getHwnd(), shader1Handle);
		//						api->clear(ClearBit::COLOR_DEPTH_STENCIL);
		//
		//						api->setStencilFunction(Face::FRONT, DepthFuncs::ALWAYS, 1, 0xFF);
		//						api->setStencilMask(0xFF);
		//						api->updateDepthStencil();
		//						api->drawArrays(PrimitiveType::TRIANGLESLIST, 0, 6);
		//
		//						auto shader2Handle = ShaderCache::getShader("scaled_color");
		//						shader2Handle->bind();
		//						api->setStencilFunction(Face::FRONT, DepthFuncs::NOT_EQUAL, 1, 0xFF);
		//						api->setStencilMask(0x00);
		//						api->depthTest(false);
		//						api->updateDepthStencil();
		//						api->drawArrays(PrimitiveType::TRIANGLESLIST, 0, 6);
		//
		//						api->setStencilMask(0xFF);
		//						api->setStencilFunction(Face::FRONT, DepthFuncs::ALWAYS, 0, 0xFF);
		//						api->depthTest(true);
		//						api->updateDepthStencil();
		//					},
		//				[](inputlayout* layout, RenderInterface* api)
		//					{
		//						BufferCache::deleteBuffer("Vertex Buffer");
		//						ShaderCache::deleteShader("color");
		//						ShaderCache::deleteShader("scaled_color");
		//						layout->release();
		//
		//						api->depthTest(false);
		//						api->stencilTest(false);
		//						api->updateDepthStencil();
		//					}
		//			});
#pragma endregion
	}

	void Renderer::update()
	{
		m_api->makeCurrent();

		m_api->setSwapInterval(0);

		if (m_api->shouldWindowClose())
		{
			rythe::core::events::exit evnt(0);
			raiseEvent(evnt);
			return;
		}

		m_api->setViewport(1, 0, 0, 600, 600, 0, 1);
		m_api->setClearColor(0x64 / 255.0f, 0x95 / 255.0f, 0xED / 255.0f, 1.0f);
		m_api->clear(ClearBit::COLOR);

		if (stopTest)
		{
			m_testScenes[lastScene]->destroy(m_api);
			stopTest = false;
		}
		else if (initializeTest)
		{
			if (lastScene == m_testScenes.size() - 1 && currentScene == 0)
			{
				writer.printResults();
				rythe::core::events::exit evnt(0);
				raiseEvent(evnt);
			}
			auto start = std::chrono::high_resolution_clock::now();
			m_testScenes[currentScene]->setup(m_api);
			auto end = std::chrono::high_resolution_clock::now();
			writer.writeSetupTime(m_testScenes[currentScene]->name, m_testScenes[currentScene]->type, std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / 1000000.0f);
			initializeTest = false;
			updateTest = true;
		}
		else if (updateTest)
		{
			auto start = std::chrono::high_resolution_clock::now();
			m_testScenes[currentScene]->update(m_api);
			auto end = std::chrono::high_resolution_clock::now();
			timeSum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / 1000000.0f;

			if (testCount >= maxTests)
			{
				writer.writeFrameTime(m_testScenes[currentScene]->name, m_testScenes[currentScene]->type, timeSum / maxTests);
				testCount = 0;
				timeSum = 0;
				key_callback(nullptr, GLFW_KEY_RIGHT, 0, GLFW_PRESS, 0);
			}
			testCount++;
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

	void Renderer::TestStencilTest()
	{
		glfwSetWindowTitle(m_api->getWindow(), "TestStencilTest");
		//auto& renderer = testEnt.getComponent<sprite_renderer>();
		//auto& layout = renderer.layout;
		//buffer_handle vertexHandle = BufferCache::getBuffer("Vertex Buffer");
		//shader_handle colorShader = ShaderCache::getShader("color");
		//shader_handle texShader = ShaderCache::getShader("default");
		//texture_handle texture = TextureCache::getTexture2D("Rythe");
		//vertex verticies[12] =
		//{	//positions									//colors								//tex coors
		//	{ { -0.1f + count, 0.1f, 0.0f},			{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//0
		//	{ {	-0.1f + count,-0.1f, 0.0f },			{ 0.0f, 1.0f, 0.0f, 1.0f },		{ 0.0f, 0.0f } },//1
		//	{ { 0.1f + count,-0.1f, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//2
		//	{ { -0.1f + count, 0.1f, 0.0f },			{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//0
		//	{ { 0.1f + count,-0.1f, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//2
		//	{ { 0.1f + count, 0.1f, 0.0f },			{ 1.0f, 1.0f, 0.0f, 1.0f },		{ 1.0f, 1.0f } },//3

		//	{ { -0.1f, 0.1f + count, 0.0f },			{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//0
		//	{ {	-0.1f,-0.1f + count, 0.0f },			{ 0.0f, 1.0f, 0.0f, 1.0f },		{ 0.0f, 0.0f } },//1
		//	{ { 0.1f,-0.1f + count, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//2
		//	{ { -0.1f, 0.1f + count, 0.0f },			{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//0
		//	{ { 0.1f,-0.1f + count, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//2
		//	{ { 0.1f, 0.1f + count, 0.0f },			{ 1.0f, 1.0f, 0.0f, 1.0f },		{ 1.0f, 1.0f } }//3
		//};

		//vertexHandle->bufferData(verticies, 12);

		//texture->bind();
		//layout.bind(m_api->getHwnd(), texShader);

		//m_api->depthTest(true);
		//m_api->setStencilOp(Face::FRONT, StencilOp::KEEP, StencilOp::KEEP, StencilOp::REPLACE);
		//m_api->updateDepthStencil();
		//m_api->clear(ClearBit::COLOR_DEPTH_STENCIL);

		//m_api->setStencilFunction(Face::FRONT, DepthFuncs::ALWAYS, 1, 0xFF);
		//m_api->setStencilMask(0xFF);
		//m_api->updateDepthStencil();
		//texShader->bind();
		//m_api->drawArraysInstanced(PrimitiveType::TRIANGLESTRIP, 12, 2, 0, 0);

		//m_api->setDepthFunction(DepthFuncs::NOT_EQUAL);
		//m_api->setStencilMask(0x00);
		//m_api->depthTest(false);
		//m_api->updateDepthStencil();
		//colorShader->bind();
		//m_api->drawArraysInstanced(PrimitiveType::TRIANGLESTRIP, 12, 2, 0, 0);

		//m_api->setStencilMask(0xFF);
		//m_api->setStencilFunction(Face::FRONT, DepthFuncs::ALWAYS, 1, 0xFF);
		//m_api->depthTest(true);
		//m_api->updateDepthStencil();

		//m_api->clear(ClearBit::STENCIL);
	}

}