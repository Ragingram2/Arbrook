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

		m_api->initialize(math::ivec2(Width, Height), "Arbrook");

		if (!m_api->getWindow())
		{
			glfwTerminate();
			log::error("Window initialization failed");
			return;
		}

		glfwSetKeyCallback(m_api->getWindow(), key_callback);

#pragma region Abstracted API

		m_testScenes.emplace_back(std::make_unique<dummy_test>());

		////DrawArrays
		m_testScenes.emplace_back(std::make_unique<API_DrawArraysTest>());
		m_testScenes.emplace_back(std::make_unique<Native_DrawArraysTest>());
		m_testScenes.emplace_back(std::make_unique<BGFX_DrawArraysTest>());

		//DrawArraysInstanced
		m_testScenes.emplace_back(std::make_unique<API_DrawArraysInstancedTest>());
		m_testScenes.emplace_back(std::make_unique<Native_DrawArraysInstancedTest>());
		m_testScenes.emplace_back(std::make_unique<BGFX_DrawArraysInstancedTest>());


		////DrawIndexed
		m_testScenes.emplace_back(std::make_unique<API_DrawIndexedTest>());
		m_testScenes.emplace_back(std::make_unique<Native_DrawIndexedTest>());
		m_testScenes.emplace_back(std::make_unique<BGFX_DrawIndexedTest>());

		////DrawIndexedInstanced
		m_testScenes.emplace_back(std::make_unique<API_DrawIndexedInstancedTest>());
		m_testScenes.emplace_back(std::make_unique<Native_DrawIndexedInstancedTest>());
		m_testScenes.emplace_back(std::make_unique<BGFX_DrawIndexedInstancedTest>());

#pragma endregion
	}

	void Renderer::update()
	{
		m_api->makeCurrent();
		m_api->setSwapInterval(0);

		m_api->setViewport(1, 0, 0, Width, Height, 0, 1);
		m_api->setClearColor(0x64 / 255.0f, 0x95 / 255.0f, 0xED / 255.0f, 1.0f);
		m_api->clear(ClearBit::COLOR);

		if (m_api->shouldWindowClose())
		{
			rythe::core::events::exit evnt(0);
			raiseEvent(evnt);
			return;
		}

		if (stopTest)
		{
			writer.writeNumObjects(m_testScenes[lastScene]->name, m_testScenes[lastScene]->type, testCount);
			testCount = 0;

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
			writer.writeSetupTime(m_testScenes[currentScene]->name, m_testScenes[currentScene]->type, std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());
			initializeTest = false;
			updateTest = true;

			if (m_testScenes[currentScene]->type == None)
			{
				testCount = maxTests * .95f;
			}
		}
		else if (updateTest)
		{
			auto start = std::chrono::high_resolution_clock::now();
			m_testScenes[currentScene]->update(m_api);
			auto end = std::chrono::high_resolution_clock::now();
			writer.writeFrameTime(m_testScenes[currentScene]->name, m_testScenes[currentScene]->type, std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());

			if (enableTesting && testCount >= maxTests)
			{
				nextScene();
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
}