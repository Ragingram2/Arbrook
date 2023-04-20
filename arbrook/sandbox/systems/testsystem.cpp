#include "sandbox/systems/testsystem.hpp"

namespace rythe::core
{
	void TestSystem::setup()
	{
		log::info("Initializing Test System");

		auto wId = registry->m_worldId;
		m_api = &registry->m_entities[wId].getComponent<gfx::RenderInterface>();

		gfx::vertex verticies[] =
		{	//positions						//colors								//tex coors
			{ { -0.1f, 0.1f, 0.0f },			{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//0
			{ {	-0.1f,-0.1f, 0.0f },			{ 0.0f, 1.0f, 0.0f, 1.0f },		{ 0.0f, 0.0f } },//1
			{ { 0.1f,-0.1f, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//2
			{ { 0.1f, 0.1f, 0.0f },			{ 1.0f, 1.0f, 0.0f, 1.0f },		{ 1.0f, 1.0f } }//3
		};

		unsigned int indicies[] =
		{
			0,1,2,
			0,2,3
		};

		m_api->makeCurrent();

		float spawnCount = 2.f;
		auto texture = gfx::TextureCache::createTexture2D(*m_api, "Rythe", "resources/textures/Rythe.png");
		auto shader = gfx::ShaderCache::createShader(*m_api, "default", "resources/shaders/default.shader");
		auto vertexHandle = gfx::BufferCache::createBuffer<gfx::vertex, float>(*m_api, "Vertex Buffer", gfx::TargetType::VERTEX_BUFFER, gfx::UsageType::STATICDRAW);
		auto indexHandle = gfx::BufferCache::createBuffer<unsigned int>(*m_api, "Index Buffer", gfx::TargetType::INDEX_BUFFER, gfx::UsageType::STATICDRAW);
		auto constantHandle = gfx::BufferCache::createBuffer<gfx::vtx_constant, float>(*m_api, "Constant Buffer", gfx::TargetType::CONSTANT_BUFFER, gfx::UsageType::STATICDRAW, nullptr, 1);

		for (int i = 0; i < spawnCount; i++)
		{
			auto& ent = createEntity();

			//These positions aren't really random as they don't take a fluxuating seed into account
			auto& transf = ent.addComponent<transform>();
			float randX = ((std::rand() % 200) / 100.f) - 1.f;
			float randY = ((std::rand() % 200) / 100.f) - 1.f;
			transf.position = math::vec3(randX, randY, 0.0f);
			log::debug("Random Pos: [{},{}]", randX, randY);

			auto& example = ent.addComponent<exampleComp>();
			example.time = (std::rand() % 10) / 10.f;
			example.inc = (((std::rand() % 10) / 10.f) - 1.f) / 100.f;

			auto& render = ent.addComponent<gfx::sprite_renderer>();
			auto& layout = render.layout;

			render.texture = texture;
			render.shader = shader;

			vertexHandle->bufferData(verticies, sizeof(verticies) / sizeof(gfx::vertex));
			indexHandle->bufferData(indicies, sizeof(indicies) / sizeof(unsigned int));

			layout.addBuffer(vertexHandle);
			layout.addBuffer(indexHandle);

			//make a Itexture
			//texture->bind();
			shader->addBuffer(gfx::ShaderType::VERTEX, constantHandle);
			shader->bind();

			layout.bind(m_api->getHwnd(), shader);
			layout.setAttributePtr("POSITION", 0, gfx::FormatType::RGB32F, sizeof(gfx::vertex), 0);
			layout.setAttributePtr("COLOR", 1, gfx::FormatType::RGBA32F, sizeof(gfx::vertex), 3.0f * sizeof(float));
			layout.setAttributePtr("TEXCOORD", 2, gfx::FormatType::RG32F, sizeof(gfx::vertex), 7.0f * sizeof(float));
			layout.submitAttributes();
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
	}

	void TestSystem::shutdown()
	{
		log::info("Shutting down Test System ");
	}
}