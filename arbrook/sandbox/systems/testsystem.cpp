#include "sandbox/systems/testsystem.hpp"
namespace rythe::core
{

	void TestSystem::setup()
	{
		log::info("Initializing Test System");

		auto wId = registry->m_worldId;
		m_api = &registry->m_entities[wId].getComponent<gfx::RenderInterface>();

		m_api->makeCurrent();
		setKeyBind<events::key_input, TestSystem, &TestSystem::key_callback>();

		float spawnCount = 10.f;
		auto texture = gfx::TextureCache::createTexture2D(*m_api, "Rythe", "resources/textures/Rythe.png");
		auto shader = gfx::ShaderCache::createShader(*m_api, "default", "resources/shaders/default.shader");
		auto vertexHandle = gfx::BufferCache::createBuffer<gfx::vertex>(*m_api, "Vertex Buffer", gfx::TargetType::VERTEX_BUFFER, gfx::UsageType::STATICDRAW);
		auto indexHandle = gfx::BufferCache::createBuffer<unsigned int>(*m_api, "Index Buffer", gfx::TargetType::INDEX_BUFFER, gfx::UsageType::STATICDRAW);
		auto constantHandle = gfx::BufferCache::createBuffer<gfx::vtx_constant>(*m_api, "Constant Buffer", gfx::TargetType::CONSTANT_BUFFER, gfx::UsageType::STATICDRAW, nullptr, 1);

		for (int i = 0; i < spawnCount; i++)
		{
			auto& ent = createEntity();

			//These positions aren't really random as they don't take a fluxuating seed into account
			auto& transf = ent.addComponent<transform>();
			float randX = ((std::rand() % 200) / 100.f) - 1.f;
			float randY = ((std::rand() % 200) / 100.f) - 1.f;
			transf.position = math::vec3(randX, randY, 0.0f);

			auto& example = ent.addComponent<exampleComp>();
			example.time = (std::rand() % 10) / 10.f;
			example.inc = (((std::rand() % 10) / 10.f) - 1.f) / 100.f;

			auto& render = ent.addComponent<gfx::sprite_renderer>();
			auto& layout = render.layout;

			vertexHandle->bufferData(render.verticies, 4);
			indexHandle->bufferData(render.indicies, 4);
			layout.addBuffer(vertexHandle);
			layout.addBuffer(indexHandle);

			shader->addBuffer(gfx::ShaderType::VERTEX, constantHandle);
			shader->bind();
			texture->bind();

			layout.bind(m_api->getHwnd(), shader);
			layout.setAttributePtr("POSITION", 0, gfx::FormatType::RGB32F, sizeof(gfx::vertex), 0);
			layout.setAttributePtr("COLOR", 1, gfx::FormatType::RGBA32F, sizeof(gfx::vertex), 3.0f * sizeof(float));
			layout.setAttributePtr("TEXCOORD", 2, gfx::FormatType::RG32F, sizeof(gfx::vertex), 7.0f * sizeof(float));
			layout.submitAttributes();

			render.texture = texture;
			render.shader = shader;

		}
	}

	void TestSystem::update()
	{
		for (auto& ent : m_filter)
		{
			auto& transf = ent.getComponent<transform>();
			transf.position += math::vec3(.02f, 0, 0);
			if (transf.position.x > 1)
			{
				transf.position.x = -1.0f;
			}

			auto& example = ent.getComponent<exampleComp>();

			if (example.time > 1.0f || example.time < 0.0f)
				example.inc = -example.inc;
			example.time += example.inc;
		}

		m_api->pollEvents();
	}

	void TestSystem::shutdown()
	{
		log::info("Shutting down Test System ");
	}

	void TestSystem::key_callback(events::key_input& input)
	{
		if (input.key == GLFW_KEY_E && input.action == GLFW_PRESS)
		{
			log::debug("E Key pressed");
		}
	}
}