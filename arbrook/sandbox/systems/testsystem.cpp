#include "sandbox/systems/testsystem.hpp"

namespace rythe::core
{
	void TestSystem::setup()
	{
		log::info("Initializing Test System");
		float verticies[] =
		{		//positions		//colors					//tex coors
				 0.1f,   0.1f,		1.0f,  0.0f, 0.0f,		1.0f, 1.0f,//0
				 0.0f, -0.1f,		0.0f, 1.0f, 0.0f,		1.0f, 0.0f,//1
				-0.1f, -0.1f,		0.0f, 0.0f, 1.0f,		0.0f,0.0f,//2
				-0.1f, 0.1f ,		1.0f, 1.0f, 0.0f,			0.0f, 1.0f//3
		};

		unsigned int indicies[] =
		{
			0,1,2/*,
			2,3,0*/
		};

		gfx::window::makeCurrent();

		float spawnCount = 5.f;
		for (int i = 0; i < spawnCount; i++)
		{
			auto& ent = createEntity();
			auto& render = ent.addComponent<gfx::shape_renderer>();
			render.vao.initialize();
			render.vao.m_vertexBuffer.bufferData(verticies, sizeof(verticies), GL_STATIC_DRAW);
			render.vao.m_vertexBuffer.setAttributePtr(0, 2, GL_FLOAT, false, 7 * sizeof(float));
			render.vao.m_vertexBuffer.setAttributePtr(1, 3, GL_FLOAT, false, 7 * sizeof(float), (void*)(3 * sizeof(float)));
			render.vao.m_vertexBuffer.setAttributePtr(2, 2, GL_FLOAT, false, 7 * sizeof(float), (void*)(5 * sizeof(float)));

			render.vao.m_indexBuffer.bufferData(indicies, sizeof(indicies), GL_STATIC_DRAW);
			render.vao.unbind();

			auto& transf = ent.addComponent<transform>();
			float randX = ((std::rand() % 200) / 100.f) - 1.f;
			float randY = ((std::rand() % 200) / 100.f) - 1.f;
			transf.position = math::vec2(randX, randY);
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
		}
	}

	void TestSystem::shutdown()
	{
		log::info("Shutting down Test System ");
	}
}