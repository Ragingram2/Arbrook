#include "game.hpp"

namespace fs = std::filesystem;
namespace ast = rythe::core::assets;
namespace rythe::game
{
	void Game::setup()
	{
		log::info("Initializing Game system");
		fs::current_path(fs::current_path().append("../../applications/sandbox/src/sandbox/"));
		bindEvent<key_input<inputmap::method::F1>, &Game::reloadShaders>();
		bindEvent<key_input<inputmap::method::MOUSE_RIGHT>, &Game::toggleMouseCapture>();

		input::InputSystem::registerWindow(gfx::Renderer::RI->getGlfwWindow());

		ast::AssetCache<gfx::texture_source>::registerImporter<gfx::TextureImporter>();
		ast::AssetCache<gfx::mesh>::registerImporter<gfx::MeshImporter>();
		ast::AssetCache<gfx::shader_source>::registerImporter<gfx::ShaderImporter>();
		ast::AssetCache<gfx::material_source>::registerImporter<gfx::MaterialImporter>();

		ast::AssetCache<gfx::texture_source>::loadAssets("resources/textures/", gfx::default_texture_import_params);
		ast::AssetCache<gfx::shader_source>::loadAssets("resources/shaders/", gfx::default_shader_params);
		gfx::ShaderCache::createShaders(ast::AssetCache<gfx::shader_source>::getAssets());
		ast::AssetCache<gfx::mesh>::loadAssets("resources/meshes/glb/", gfx::default_mesh_params);
		ast::AssetCache<gfx::material_source>::loadAssets("resources/materials/", gfx::default_material_params);
		gfx::MaterialCache::loadMaterial("error");
		gfx::ModelCache::loadModels(ast::AssetCache<gfx::mesh>::getAssets());
		gfx::MaterialCache::loadMaterials(ast::AssetCache<gfx::material_source>::getAssets());

		gfx::TextureCache::createTexture2D("park", ast::AssetCache<gfx::texture_source>::getAsset("park"), gfx::texture_parameters
			{
				.usage = gfx::UsageType::IMMUTABLE
			});

		gfx::TextureCache::createTexture2D("bricks_normal", ast::AssetCache<gfx::texture_source>::getAsset("bricks_normal"), gfx::texture_parameters
			{
				.wrapModeS = gfx::WrapMode::REPEAT,
				.wrapModeT = gfx::WrapMode::REPEAT,
				.minFilterMode = gfx::FilterMode::LINEAR_MIPMAP_LINEAR,
				.magFilterMode = gfx::FilterMode::LINEAR
			});


		mat = gfx::MaterialCache::getMaterial("default");

		colorMat = gfx::MaterialCache::getMaterial("color");
		colorMat->getShader()->addBuffer(gfx::BufferCache::createConstantBuffer<math::vec4>("Color", 3, gfx::UsageType::STATICDRAW));
		math::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
		colorMat->setUniform("Color", &color, 3);

		{
			auto& skyboxRenderer = registry->world.addComponent<gfx::skybox_renderer>();
			skyboxRenderer.skyboxTex = gfx::TextureCache::getTexture("park");
		}

		{
			auto ent = createEntity("Floor");
			auto& transf = ent.addComponent<core::transform>();
			transf.scale = math::vec3(20, .5f, 20);
			transf.position = math::vec3::zero;
			ent.addComponent<gfx::mesh_renderer>({ .mainMaterial = mat, .model = gfx::ModelCache::getModel("cube") ,.castShadows = false });
			ent.addComponent<physics::rigidbody>({ .mass = 1.0f, .motionType = JPH::EMotionType::Static, .activationType = JPH::EActivation::DontActivate });
			ent.addComponent<physics::collider>({ .bounds = math::vec3(20.0f,0.5f,20.0f) });
		}

		{
			auto ent = createEntity("Sponza");
			auto& transf = ent.addComponent<core::transform>();
			transf.scale = math::vec3::one * 10.0f;
			transf.position = math::vec3(0.0f, 10.0f, 0.0f);
			ent.addComponent<gfx::mesh_renderer>({ .mainMaterial = gfx::MaterialCache::getMaterial("sponza-material"), .model = gfx::ModelCache::getModel("sponza"), .castShadows = true });
		}

		{
			auto ent = createEntity("Entity");
			auto& transf = ent.addComponent<core::transform>();
			transf.scale = math::vec3::one;
			transf.position = math::vec3(0.0f, 10.0f, 0.0f);
			transf.rotation = math::quat::from_euler(math::vec3(-90.0f, 0.0f, 0.0f) * math::deg2rad<float>());
			ent.addComponent<gfx::mesh_renderer>({ .mainMaterial = gfx::MaterialCache::getMaterial("bog"), .model = gfx::ModelCache::getModel("cube"), .castShadows = true });
			ent.addComponent<physics::rigidbody>({ .mass = 1.0f, .motionType = JPH::EMotionType::Dynamic, .activationType = JPH::EActivation::Activate });
			ent.addComponent<physics::collider>({.bounds = math::vec3(1.0f,1.0f,1.0f)});
			//auto child = createEntity("child");
			//ent->children.insert(child);
		}

		{
			auto ent = createEntity("Directional Light");
			auto& transf = ent.addComponent<core::transform>();
			transf.scale = math::vec3::one;
			transf.position = math::vec3(0.0f, 25.f, 0.0f);
			transf.rotation = math::quat::from_euler(math::vec3(-90.0f, 0.0f, 0.0f) * math::deg2rad<float>());
			auto& light = ent.addComponent<gfx::light>({ .type = gfx::LightType::DIRECTIONAL });
			light.asDirectionalLight().color = math::vec4(1.0f);
			light.asDirectionalLight().intensity = 1.0f;
			ent.addComponent<gfx::mesh_renderer>({ .mainMaterial = colorMat, .model = gfx::ModelCache::getModel("cone"), .castShadows = false });
		}

		{
			auto ent = createEntity("Point Light");
			ent.addComponent<core::transform>({ .scale = math::vec3(.1f, .1f, .1f), .position = math::vec3(0.0f, 10.0f, 0.0f) });
			auto& light = ent.addComponent<gfx::light>({ .type = gfx::LightType::POINT });
			light.asPointLight().color = math::vec4(1.0f);
			light.asPointLight().intensity = 1.0f;
			light.asPointLight().range = 100.0f;
			ent.addComponent<core::examplecomp>({ .direction = math::vec3::up, .range = 10.0f, .speed = 20.0f });
			ent.addComponent<gfx::mesh_renderer>({ .mainMaterial = gfx::MaterialCache::getMaterial("red"), .model = gfx::ModelCache::getModel("icosphere") ,.castShadows = false });
		}

		{
			auto camera = createEntity("Camera");
			auto& camTransf = camera.addComponent<core::transform>();
			camTransf.position = math::vec3(0.0f, 10.0f, -10.0f);
			camTransf.rotation = math::quat::look_at(math::vec3::zero, camTransf.forward(), camTransf.up());
			camTransf.scale = math::vec3(1.0f);
			camera.addComponent<gfx::camera>({ .farZ = 10000.f, .nearZ = 0.1f, .fov = 80.f });
			camera.addComponent<camera_settings>({ .mode = CameraControlMode::FreeLook, .speed = 10.0f, .sensitivity = .9f });
		}

		//future = TimerAsync(5s, [=]() { serializeScene(); });
		//serializeScene();
	}

	void Game::update()
	{
		ZoneScopedN("Game Update");

		//auto deltaTime = static_cast<std::chrono::duration<float, std::milli>>(core::Time::deltaTime);
		//auto status = future.wait_for(deltaTime);
		//if (status == std::future_status::ready)
		//{
		//	log::debug("Done");
		//}
	}

	void Game::serializeScene()
	{
		//sceneHierarchy.push_back(rfl::json::write(core::ecs::Registry::entities[core::ecs::Registry::worldId]));
		//log::debug(sceneHierarchy.dump());
	}
}