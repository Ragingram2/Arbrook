#include "sandbox/systems/testsystem.hpp"

namespace rythe::core
{
	void TestSystem::setup()
	{
		log::info("Initializing Test System");
		float positions[] =
		{
			-0.1f, -0.1f,//0
			 0.1f, -0.1f,//1
			 0.1f,  0.1f,//2
			-0.1f, 0.1f //3
		};

		unsigned int indicies[] =
		{
			0,1,2,
			2,3,0
		};

		gfx::window::makeCurrent();

		float spawnCount = 5.f;
		for (int i = 0; i < spawnCount; i++)
		{
			auto& ent = createEntity();
			auto& render = ent.addComponent<gfx::shape_renderer>();
			gfx::buffer<gfx::vertex, float> posBuffer;
			render.vertexBuffer = posBuffer;
			render.vertexBuffer.bufferData(positions, sizeof(positions), GL_STATIC_DRAW);
			render.vertexBuffer.setAttributePtr(0, 2, GL_FLOAT, false);
			render.vertexBuffer.unbind();

			gfx::buffer<gfx::index, unsigned int> indBuffer;
			render.indexBuffer = indBuffer;
			render.indexBuffer.bufferData(indicies, sizeof(indicies), GL_STATIC_DRAW);
			render.indexBuffer.unbind();

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