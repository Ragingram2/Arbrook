#include "sandbox/systems/game.hpp"

namespace rythe::game
{
	void Game::setup()
	{
		EventBus::bind<key_input, Game, &Game::reloadShaders>(*this);
		std::vector<math::vec4> positions
		{	//positions						
			{ -1.f, 1.0f, 0.0f,1.0f },//0
			{-1.f,-1.0f, 0.0f,1.0f  },//1
			{  1.0f,-1.0f, 0.0f,1.0f },//2
			{ -1.0f, 1.0f, 0.0f ,1.0f},//0
			{  1.0f,-1.0f, 0.0f,1.0f },//2
			{  1.0f, 1.0f, 0.0f,1.0f }//3
		};
		std::vector<math::vec2> uvs
		{
				{ 0, 1 },
				{ 0, 0 },
				{ 1, 0 },
				{ 0, 1 },
				{ 1, 0 },
				{ 1, 1 }
		};

		mat.m_shader = gfx::ShaderCache::createShader("default", "resources/shaders/default.shader");
		mat.m_texture = gfx::TextureCache::createTexture2D("Rythe", "resources/textures/Rythe.png");
		msh.vertices = positions;
		msh.texCoords = uvs;

		ent = createEntity("Cube");
		auto& transf = ent.addComponent<core::transform>();
		transf.position = math::vec3(.5f, 0, .2f);
		auto& renderer = ent.addComponent<gfx::mesh_renderer>();
		renderer.set_material(mat);
		renderer.set_mesh(msh);

		//camera = createEntity();
		//auto& transf = camera.addComponent<core::transform>();
		//transf.position = math::vec3(1.0);
		//camera.addComponent<gfx::camera>();
	}


}