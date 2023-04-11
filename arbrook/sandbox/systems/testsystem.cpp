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
			{ { -0.1f, 0.1f, 0.0f },			{ 1.0f, 0.0f, 0.0f, 1.0f }},		//{ 0.0f, 1.0f } },//0
			{ {	-0.1f,-0.1f, 0.0f },			{ 0.0f, 1.0f, 0.0f, 1.0f }},		//{ 0.0f, 0.0f } },//1
			{ { 0.1f,-0.1f, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f }},		//{ 1.0f, 0.0f } },//2
			{ { 0.1f, 0.1f, 0.0f },			{ 1.0f, 1.0f, 0.0f, 1.0f }}		//{ 1.0f, 1.0f } }//3
		};

		unsigned int indicies[] =
		{
			0,2,1,
			2,3,0
		};

		m_api->makeCurrent();

		auto texture = gfx::TextureCache::createTexture2D(*m_api, "Rythe", "resources/textures/Rythe.png");
		auto shader = gfx::ShaderCache::createShader(*m_api, "default", "resources/shaders/default.shader");

		float spawnCount = 1.f;
		for (int i = 0; i < spawnCount; i++)
		{
			auto& ent = createEntity();

			auto& render = ent.addComponent<gfx::sprite_renderer>();
			auto& layout = render.layout;

			m_api->bind(shader);
			m_api->bind(texture);
			render.texture = texture;
			render.shader = shader;

			auto handle = gfx::BufferCache::createBuffer<gfx::vertex, float>(*m_api, "Vertex Buffer", gfx::TargetType::ARRAY_BUFFER, gfx::UsageType::StaticDraw, verticies, sizeof(verticies));
			layout.addBuffer(handle);
			handle = gfx::BufferCache::createBuffer<unsigned int>(*m_api, "Index Buffer", gfx::TargetType::ELEMENT_ARRAY_BUFFER, gfx::UsageType::StaticDraw, indicies, sizeof(indicies));
			layout.addBuffer(handle);

			layout.bind(m_api->getHwnd(), shader);

			layout.setAttributePtr("POSITION", 0, gfx::FormatType::RGB32F, sizeof(gfx::vertex), 0);
			layout.setAttributePtr("COLOR", 0, gfx::FormatType::RGBA32F, sizeof(gfx::vertex), sizeof(math::vec3));
			//vao.setAttributePtr("TEXCOORD", 2, gfx::FormatType::RG32F, sizeof(gfx::vertex), (7 * sizeof(float)));
			layout.submitAttributes();

			layout.unbind();


			auto& transf = ent.addComponent<transform>();
			float randX = ((std::rand() % 200) / 100.f) - 1.f;
			float randY = ((std::rand() % 200) / 100.f) - 1.f;
			transf.position = math::vec2(randX, randY);

			auto& example = ent.addComponent<exampleComp>();
			example.time = (std::rand() % 10) / 10.f;
			example.inc = (((std::rand() % 10) / 10.f) - 1.f) / 100.f;
		}
	}

	void TestSystem::update()
	{
		for (auto& ent : m_filter)
		{
			auto& transf = ent.getComponent<transform>();
			transf.position += math::vec2(.02f, 0);
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