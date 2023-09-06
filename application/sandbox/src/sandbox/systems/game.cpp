#include "sandbox/systems/game.hpp"

namespace rythe::game
{
	void Game::setup()
	{
		EventBus::bind<key_input, Game, &Game::reloadShaders>(*this);
		EventBus::bind<key_input, Game, &Game::move>(*this);

		//std::vector<math::vec4> positions
		//{	//positions						
		//	{ -1.0f, 1.0f, 0.0f, 1.0f },//0
		//	{ -1.0f,-1.0f, 0.0f, 1.0f  },//1
		//	{  1.0f,-1.0f, 0.0f, 1.0f },//2
		//	{ -1.0f, 1.0f, 0.0f, 1.0f},//0
		//	{  1.0f,-1.0f, 0.0f, 1.0f },//2
		//	{  1.0f, 1.0f, 0.0f, 1.0f }//3
		//};
		//std::vector<math::vec2> uvs
		//{
		//		{ 0, 1 },
		//		{ 0, 0 },
		//		{ 1, 0 },
		//		{ 0, 1 },
		//		{ 1, 0 },
		//		{ 1, 1 }
		//};

		std::vector<math::vec4> positions
		{
			//Back
			 { -0.1f,  0.1f, -0.1f,1.0f	},//0
			 {  0.1f, -0.1f, -0.1f,1.0f	},
			 { -0.1f, -0.1f, -0.1f,1.0f	 },

			 { -0.1f,  0.1f, -0.1f,1.0f	},
			 {  0.1f,  0.1f, -0.1f,1.0f		},
			 {  0.1f, -0.1f, -0.1f,1.0f	},

			 //Front
			  { -0.1f,  0.1f, 0.1f,1.0f		},
			  { -0.1f, -0.1f, 0.1f,1.0f	},
			  {  0.1f, -0.1f, 0.1f,1.0f		},

			  { -0.1f,  0.1f, 0.1f,1.0f		},
			  {  0.1f, -0.1f, 0.1f,1.0f		},
			  {  0.1f,  0.1f, 0.1f,1.0f		},

			  //Left
			   {	0.1f, 0.1f, -0.1f,1.0f		},
			   {	0.1f, -0.1f, 0.1f,1.0f		},
			   {	0.1f, -0.1f,-0.1f,1.0f		},

			   {	0.1f, 0.1f, -0.1f	,1.0f		},
			   {	0.1f, 0.1f,  0.1f	,1.0f		},
			   {0.1f, -0.1f, 0.1f,1.0f		},

			   //Right
				{	-0.1f,0.1f, -0.1f	,1.0f		},
				{	-0.1f, -0.1f,-0.1f,1.0f	},
				{	-0.1f, -0.1f, 0.1f,1.0f		},

				{	-0.1f, 0.1f, -0.1f,1.0f		},
				{-0.1f, -0.1f, 0.1f,1.0f		},
				{	-0.1f, 0.1f,  0.1f,1.0f		},

				//Bottom
				 { -0.1f, -0.1f,  0.1f,1.0f	},
				 { -0.1f, -0.1f, -0.1f,1.0f	},
				 {  0.1f, -0.1f, -0.1f,1.0f	},

				 { -0.1f, -0.1f,  0.1f,1.0f	},
				 {  0.1f, -0.1f, -0.1f,1.0f	},
				 {  0.1f, -0.1f,  0.1f,1.0f		},

				 //Top
				  { -0.1f, 0.1f,  0.1f,1.0f		},
				  {  0.1f, 0.1f, -0.1f,1.0f		},
				  { -0.1f, 0.1f, -0.1f,1.0f		},

				  { -0.1f, 0.1f,  0.1f,1.0f		},
				  {  0.1f, 0.1f	,  0.1f,1.0f	},
				  {  0.1f, 0.1f, -0.1f,1.0f		}
		};

		std::vector<math::vec2> uvs
		{
			{	1.0f, 1.0f	},
			{	0.0f, 0.0f	},
			{	1.0f, 0.0f	},

			{	1.0f, 1.0f	},
			{	0.0f, 1.0f	},
			{	0.0f, 0.0f	},


			{	0.0f, 1.0f	},
			{	0.0f, 0.0f	},
			{	1.0f, 0.0f	},

			{	0.0f, 1.0f	},
			{	1.0f, 0.0f	},
			{	1.0f, 1.0f	},


			{	1.0f, 1.0f	},
			{	0.0f, 0.0f	},
			{	1.0f, 0.0f	},

			{	1.0f, 1.0f	},
			{	0.0f, 1.0f	},
			{	0.0f, 0.0f },


			{	0.0f, 1.0f	},
			{	0.0f, 0.0f	},
			{	1.0f, 0.0f	},

			{	0.0f, 1.0f	},
			{	1.0f, 0.0f },
			{	1.0f, 1.0f	},

			{	0.0f, 1.0f	},
			{	0.0f, 0.0f	},
			{	1.0f, 0.0f	},

			{	0.0f, 1.0f	},
			{	1.0f, 0.0f	},
			{	1.0f, 1.0f	},


			{	0.0f, 1.0f	},
			{	1.0f, 0.0f	},
			{	0.0f, 0.0f	},

			{	0.0f, 1.0f	},
			{	1.0f, 1.0f	},
			{	1.0f, 0.0f	}
		};

		mat.m_shader = gfx::ShaderCache::createShader("default", "resources/shaders/default.shader");
		mat.m_texture = gfx::TextureCache::createTexture2D("Rythe", "resources/textures/Rythe.png");
		msh.vertices = positions;
		msh.texCoords = uvs;

		ent = createEntity("Cube");
		auto& transf = ent.addComponent<core::transform>();
		transf.scale = math::vec3(0.7f, 0.7f, 0.7f);
		transf.position = math::vec3(0.0f, 0.0f, .5f);

		auto& renderer = ent.addComponent<gfx::mesh_renderer>();
		renderer.set_material(mat);
		renderer.set_mesh(msh);

		camera = createEntity("Camera");
		auto& camTransf = camera.addComponent<core::transform>();
		camTransf.position = math::vec3(0.0f, 0.0f, -0.2f);
		auto& cam = camera.addComponent<gfx::camera>();
		cam.farZ = 1000.f;
		cam.nearZ = .01f;
		cam.fov = 90.f;
		cam.calculate_projection();
		cam.calculate_view(camTransf.position.get(), math::normalize(camTransf.position + camTransf.forward()), camTransf.up());
		//log::debug("Perspective Matrix\n{}", cam.projection);
		//log::debug("View Matrix\n{}", cam.view);
		//log::debug("ProjeView\n{}", cam.projection * cam.view);
		//log::debug("MVP\n{}", cam.projection * cam.view * transf.localMatrix.get());
	}

	void Game::update()
	{
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;


		auto& transf = camera.getComponent<core::transform>();
		transf.position += deltaTime * inputVec;
		transf.rotation = math::quat(math::rotate(transf.localMatrix.get(), math::deg2rad(degrees), transf.up()));
		auto& cam = camera.getComponent<gfx::camera>();
		cam.calculate_view(transf.position.get(), math::normalize(transf.position + transf.forward()));
		//log::debug("Degrees {}", degrees);
		//log::debug("Forward {}", transf.forward());
	}

}