#include "sandbox/systems/game.hpp"

namespace rythe::game
{
	void Game::setup()
	{
		log::debug("Initializing Game system");
		EventBus::bind<key_input, Game, &Game::reloadShaders>(*this);
		EventBus::bind<key_input, Game, &Game::move>(*this);
		EventBus::bind<key_input, Game, &Game::toggleMouseCapture>(*this);
		EventBus::bind<mouse_input, Game, &Game::mouselook>(*this);

		input::InputSystem::registerWindow(gfx::Renderer::RI->getGlfwWindow());

		gfx::gui_stage::addGuiRender<Game, &Game::guiRender>(this);

		gfx::ModelCache::loadModels("resources/meshes/glb/");
		gfx::TextureCache::loadTextures("resources/textures/");
		//gfx::ShaderCache::loadShaders("resources/shaders/");
		modelHandle = gfx::ModelCache::getModel("sponza");

		mat = gfx::MaterialCache::loadMaterialFromFile("default", "resources/shaders/ogl_lit.shader");
		mat.diffuse = gfx::TextureCache::getTexture2D("container_diffuse");
		mat.specular = gfx::TextureCache::getTexture2D("container_specular");

		//color = gfx::MaterialCache::loadMaterialFromFile("color", "resources/shaders/color.shader");

		cube = createEntity("Sponza");
		auto& transf = cube.addComponent<core::transform>();
		transf.scale = math::vec3::one;
		transf.position = math::vec3(0.0f, -1.0f, 10.f);

		cube.addComponent<gfx::mesh_renderer>({ .material = mat, .model = modelHandle});

		/*{
			auto ent = createEntity("Armadillio");
			auto& transf = ent.addComponent<core::transform>();
			transf.scale = math::vec3::one;
			transf.position = math::vec3(-10.0f, -1.0f, 0.0f);

			ent.addComponent<gfx::mesh_renderer>({ .material = mat, .model = gfx::ModelCache::getModel("armadillo") });
		}

		{
			auto ent = createEntity("Suzanne");
			auto& transf = ent.addComponent<core::transform>();
			transf.scale = math::vec3::one;
			transf.position = math::vec3(0.0f, -1.0f, -10.0f);

			ent.addComponent<gfx::mesh_renderer>({ .material = mat, .model = gfx::ModelCache::getModel("suzanne") });
		}

		{
			auto ent = createEntity("Teapot");
			auto& transf = ent.addComponent<core::transform>();
			transf.scale = math::vec3::one;
			transf.position = math::vec3(10.0f, -1.0f, 0.0f);

			ent.addComponent<gfx::mesh_renderer>({ .material = mat, .model = gfx::ModelCache::getModel("teapot") });
		}

		{
			auto ent = createEntity("Icosphere");
			auto& transf = ent.addComponent<core::transform>();
			transf.scale = math::vec3::one;
			transf.position = math::vec3(0.0f, 10.0f, 0.0f);

			ent.addComponent<gfx::mesh_renderer>({ .material = mat, .model = gfx::ModelCache::getModel("icosphere") });
		}

		{
			auto ent = createEntity("Bunny");
			auto& transf = ent.addComponent<core::transform>();
			transf.scale = math::vec3::one;
			transf.position = math::vec3(0.0f, -10.0f, 0.0f);

			ent.addComponent<gfx::mesh_renderer>({ .material = mat, .model = gfx::ModelCache::getModel("bunny") });
		}
		*/
		{
			auto ent = createEntity("Light");
			auto& transf = ent.addComponent<core::transform>();
			transf.scale = math::vec3::one;
			transf.position = math::vec3(0.0f, 0.0f, 0.0f);
			ent.addComponent<gfx::light>({ .type = gfx::LightType::DIRECTIONAL, .data.color = math::vec4(1.0f) });
		}
		
		{
			auto ent = createEntity("PointLight");
			ent.addComponent<core::transform>({ .scale = math::vec3(.1f, .1f, .1f), .position = math::vec3(0.0f,6.0f,7.0f) });
			ent.addComponent<gfx::light>({ .type = gfx::LightType::POINT, .data.color = math::vec4(1.0f,0.0f,0.0f,1.0f), .data.intensity = 1.0f, .data.range = 50.f });
			ent.addComponent<core::examplecomp>({ .direction = 1,.range = 10.0f,.speed = .02f });
			ent.addComponent<gfx::mesh_renderer>({.material = mat, .model = gfx::ModelCache::getModel("icosphere")});
		}

		camera = createEntity("Camera");
		auto& camTransf = camera.addComponent<core::transform>();
		camTransf.position = math::vec3(0.0f, 0.0f, 0.0f);
		camTransf.rotation = math::quat(math::lookAt(math::vec3::zero, camTransf.forward(), camTransf.up()));
		camera.addComponent<gfx::camera>({ .farZ = 10000.f, .nearZ = 1.0f, .fov = 90.f });
	}

	void Game::update()
	{
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		auto& camTransf = camera.getComponent<core::transform>();

		camTransf.position += velocity;
		velocity = math::vec3::zero;

		camTransf.rotation = math::conjugate(math::toQuat(math::lookAt(math::vec3::zero, front, up)));
	}

	void Game::guiRender()
	{
		using namespace ImGui;
		ShowDemoWindow();
		Begin("Inspector");
		if (CollapsingHeader("MeshRenderer"))
		{
			auto models = gfx::ModelCache::getModels();
			auto modelNames = gfx::ModelCache::getModelNamesC();
			Text("Here is where you can select which model to render");
			static gfx::model_handle currentSelected = modelHandle;
			if (BeginCombo("Model Dropdown", currentSelected->name.c_str()))
			{
				for (auto handle : models)
				{
					const bool is_selected = (currentSelected == handle);
					if (Selectable(handle->name.c_str(), is_selected))
						currentSelected = handle;

					if (is_selected)
					{
						SetItemDefaultFocus();
					}
				}
				setModel(currentSelected);
				EndCombo();
			}
		}

		//auto& cam = camera.getComponent<gfx::camera>();
		auto& transf = camera.getComponent<core::transform>();
		if (CollapsingHeader("DebugInfo", ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_DefaultOpen))
		{
			Text("Mouse Attributes");
			InputScalarN("Mouse Position", ImGuiDataType_Float, mousePos.data, 2, 0, 0, 0, ImGuiInputTextFlags_ReadOnly);

			Text("Camera Transform");
			InputScalarN("Position", ImGuiDataType_Float, transf.position.data, 3, 0, 0, 0, ImGuiInputTextFlags_ReadOnly);
			InputScalarN("Rotation", ImGuiDataType_Float, transf.rotation.data, 4, 0, 0, 0, ImGuiInputTextFlags_ReadOnly);
			InputScalarN("Scale", ImGuiDataType_Float, transf.scale.data, 3, 0, 0, 0, ImGuiInputTextFlags_ReadOnly);
		}

		ImGui::End();
	}

	void Game::reloadShaders(core::events::key_input& input)
	{
		if (input.value)
		{
			switch (input.key)
			{
			case inputmap::method::NUM1:
				gfx::ShaderCache::reloadShaders();
				break;
			default:
				break;
			}
		}
	}

	void Game::move(core::events::key_input& input)
	{
		auto& transf = camera.getComponent<core::transform>();
		if (input.value)
		{
			switch (input.key)
			{
			case inputmap::method::A:
			case inputmap::method::LEFT:
				velocity -= transf.right() * speed * deltaTime;
				break;
			case inputmap::method::D:
			case inputmap::method::RIGHT:
				velocity += transf.right() * speed * deltaTime;
				break;
			case inputmap::method::S:
			case inputmap::method::DOWN:
				velocity -= transf.forward() * speed * deltaTime;
				break;
			case inputmap::method::W:
			case inputmap::method::UP:
				velocity += transf.forward() * speed * deltaTime;
				break;
			case inputmap::method::Q:
				velocity -= math::vec3::up * speed * deltaTime;
				break;
			case inputmap::method::E:
				velocity += math::vec3::up * speed * deltaTime;
				break;
			default:
				break;
			}
		}
	}

	void Game::mouselook(core::events::mouse_input& input)
	{
		if (!input::InputSystem::mouseCaptured) return;

		static bool firstMouse = true;

		if (firstMouse)
		{
			lastMousePos = input.lastPosition;
			firstMouse = false;
		}

		mousePos = input.position;
		mouseDelta = input.positionDelta;
		lastMousePos = input.lastPosition;

		rotationDelta = math::vec2(mouseDelta.x * sensitivity, mouseDelta.y * sensitivity);

		pitch = math::clamp(pitch + rotationDelta.y, -89.99f, 89.99);
		yaw += -rotationDelta.x;

		front.x = cos(math::radians(yaw)) * cos(math::radians(pitch));
		front.y = sin(math::radians(pitch));
		front.z = sin(math::radians(yaw)) * cos(math::radians(pitch));
		front = math::normalize(front);
		right = math::normalize(math::cross(front, math::vec3::up));
		up = math::normalize(math::cross(right, front));
	}

	void Game::setModel(gfx::model_handle handle)
	{
		auto& renderer = cube.getComponent<gfx::mesh_renderer>();
		if (renderer.model != handle)
		{
			renderer.model = handle;
			renderer.dirty = true;
		}
	}
}