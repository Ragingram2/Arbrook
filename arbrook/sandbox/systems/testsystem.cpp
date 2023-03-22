#include "sandbox/systems/testsystem.hpp"

namespace rythe::core
{
	void TestSystem::setup()
	{
		log::info("Initializing Test System");
		float verticies[] =
		{		//positions		//colors					//tex coors
				 -0.1f,   0.1f,		1.0f,  0.0f, 0.0f,		0.0f, 1.0f,//0
				 -0.1f, -0.1f,		0.0f, 1.0f, 0.0f,		0.0f, 0.0f,//1
				  0.1f, -0.1f,		0.0f, 0.0f, 1.0f,		1.0f,0.0f,//2
				  0.1f, 0.1f ,		1.0f, 1.0f, 0.0f,			1.0f, 1.0f//3
		};

		unsigned int indicies[] =
		{
			0,1,2,
			2,3,0
		};

		gfx::internal::window::makeCurrent();

		auto texture = gfx::TextureCache::createTexture2D("Rythe", "resources/textures/Rythe.png");
		auto shader = gfx::ShaderCache::createShader("default", "resources/shaders/default.shader");
		float spawnCount = 5.f;
		for (int i = 0; i < spawnCount; i++)
		{
			auto& ent = createEntity();

			auto& render = ent.addComponent<gfx::sprite_renderer>();
			auto& vao = render.vao;
			vao.initialize();
			vao.bufferVertexData(verticies, sizeof(verticies));
			vao.setAttributePtr(0, 2, gfx::DataType::FLOAT, false, 7 * sizeof(float));
			vao.setAttributePtr(1, 3, gfx::DataType::FLOAT, false, 7 * sizeof(float), (void*)(3 * sizeof(float)));
			vao.setAttributePtr(2, 2, gfx::DataType::FLOAT, false, 7 * sizeof(float), (void*)(5 * sizeof(float)));

			vao.bufferIndexData(indicies, sizeof(indicies));
			m_renderAPI.bind(texture);
			m_renderAPI.bind(shader);
			render.m_texture = texture;
			render.m_shader = shader;

			vao.unbind();

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