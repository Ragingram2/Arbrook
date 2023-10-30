#include "sandbox/systems/testsystem.hpp"

namespace rythe::testing
{
	void TestSystem::setup()
	{
		log::debug("Initializing TestSystem");

		gfx::render_stage::addRender<TestSystem, &TestSystem::testRender>(this);
		gfx::gui_stage::addGuiRender<TestSystem, &TestSystem::guiRender>(this);

		gfx::ModelCache::loadModels("resources/meshes/");
		gfx::TextureCache::loadTextures("resources/textures/");
		gfx::ShaderCache::loadShaders("resources/shaders/");

		//m_testScenes.emplace(APIType::None, std::vector<std::unique_ptr<rendering_test>>());
		m_testScenes.emplace(APIType::Arbrook, std::vector<std::unique_ptr<rendering_test>>());
		m_testScenes[APIType::Arbrook].emplace_back(std::make_unique<DrawIndexedInstancedTest<APIType::Arbrook>>());

		m_testScenes.emplace(APIType::BGFX, std::vector<std::unique_ptr<rendering_test>>());
		m_testScenes[APIType::BGFX].emplace_back(std::make_unique<DrawIndexedInstancedTest<APIType::BGFX>>());

		m_testScenes.emplace(APIType::Native, std::vector<std::unique_ptr<rendering_test>>());
		m_testScenes[APIType::Native].emplace_back(std::make_unique<DrawIndexedInstancedTest<APIType::Native>>());

		testEntity = createEntity("Entity");
		{
			testEntity.addComponent<core::transform>();
			auto& testRenderer = testEntity.addComponent<test_renderer>();
			testRenderer.test = m_testScenes[currentType][0].get();
		}
		cameraEntity = createEntity("Camera");
		{
			auto& transf = cameraEntity.addComponent<core::transform>();
			transf.position = cameraPos;
			transf.rotation = math::quat(math::lookAt(cameraPos, cameraPos + math::vec3::forward, cameraUp));
			auto& cam = cameraEntity.addComponent<gfx::camera>();
			cam.farZ = 100.f;
			cam.nearZ = 1.0f;
			cam.fov = 90.f;
		}
	}

	void TestSystem::update()
	{
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}

	void TestSystem::testRender(core::transform transf, gfx::camera cam)
	{
		for (auto ent : m_filter)
		{
			auto& testRenderer = ent.getComponent<test_renderer>();

			if (!testRenderer.test->initialized)
				testRenderer.test->setup(cam, transf);
			testRenderer.test->update(cam, transf);
		}
	}

	void TestSystem::guiRender()
	{
		using namespace ImGui;
		auto& testRenderer = testEntity.getComponent<test_renderer>();
		Begin("Set Test");
		ShowDemoWindow();

		Text("Here is where you can select which API to use for rendering");
		static const char* typeNames[] = { "Arbrook","BGFX","Native" };
		if (BeginCombo("API Dropdown", typeNames[currentType]))
		{
			for (int i = 0; i < 3; i++)
			{
				const bool is_selected = (currentType == i);
				if (Button(typeNames[i]))
				{
					currentType = static_cast<APIType>(i);
					testRenderer.test->destroy();
					testRenderer.test = m_testScenes[currentType][0].get();
				}

				if (is_selected)
				{
					SetItemDefaultFocus();
				}
			}
			EndCombo();
		}

		Text("Here is where you can select which rendering test to run");
		static int currentTestSelected = 0;
		static const char* testNames[] = { "DrawIndexedInstanced"};
		if (BeginCombo("Test Dropdown", testNames[currentTestSelected]))
		{
			for (int i = 0; i < 1; i++)
			{
				const bool is_selected = (currentTestSelected == i);
				if (Selectable(testNames[i], is_selected))
					currentTestSelected = i;

				if (is_selected)
				{
					SetItemDefaultFocus();
				}
			}
			EndCombo();
		}

		if (Button("Run Test"))
		{
			//auto& testRenderer = testEntity.getComponent<test_renderer>();
			//testRenderer.test->destroy();
			//testRenderer.test = m_testScenes[currentType][0].get();
		}

		ImGui::End();
	}
}