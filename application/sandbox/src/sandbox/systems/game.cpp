#include "sandbox/systems/game.hpp"

namespace rythe::game
{
	void Game::setup()
	{
		EventBus::bind<key_input, Game, &Game::reloadShaders>(*this);
		EventBus::bind<key_input, Game, &Game::move>(*this);
		EventBus::bind<key_input, Game, &Game::debugInfo>(*this);
		//EventBus::bind<key_input, Game, &Game::randomModel>(*this);
		EventBus::bind<key_input, Game, &Game::randomShader>(*this);
		EventBus::bind<mouse_input, Game, &Game::mouselook>(*this);

		gfx::gui_stage::addGuiRender<Game, &Game::guiRender>(this);

		gfx::ModelCache::loadModels("resources/meshes/");
		//gfx::ModelCache::createModel("Armadillo", "resources/meshes/armadillo.obj");
		//gfx::ModelCache::createModel("Alligator", "resources/meshes/alligator.obj");
		//gfx::ModelCache::createModel("Beast", "resources/meshes/beast.obj");
		//gfx::ModelCache::createModel("Bunny", "resources/meshes/bunny.obj");
		//gfx::ModelCache::createModel("Suzanne", "resources/meshes/suzanne.obj");
		//gfx::ModelCache::createModel("Teapot", "resources/meshes/teapot.obj");
		modelHandle = gfx::ModelCache::getModel("suzanne");

		mat = gfx::MaterialCache::loadMaterialFromFile("default", "resources/shaders/cube.shader", "resources/textures/Rythe.png");

		ent = createEntity("Cube");
		auto& transf = ent.addComponent<core::transform>();
		transf.scale = math::vec3(1.0f, 1.0f, 1.0f);
		transf.position = math::vec3(0.0f, -1.0f, 10.f);

		auto& renderer = ent.addComponent<gfx::mesh_renderer>();
		renderer.material = mat;
		renderer.model = modelHandle;

		camera = createEntity("Camera");
		auto& camTransf = camera.addComponent<core::transform>();
		camTransf.position = math::vec3(0.0f, 0.0f, 0.0f);
		camTransf.rotation = math::quat(math::lookAt(camPos, camPos + math::vec3::forward, cameraUp));
		auto& cam = camera.addComponent<gfx::camera>();
		cam.farZ = 100.f;
		cam.nearZ = 1.0f;
		cam.fov = 90.f;
	}

	void Game::update()
	{
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}

	void Game::guiRender()
	{
		using namespace ImGui;
		Begin("Change Model");
		auto models = gfx::ModelCache::getModels();
		auto modelNames = gfx::ModelCache::getModelNamesC();
		ShowDemoWindow();
		Text("Here is where you can select which model to render");
		static int currentIdx = 0;
		if (BeginCombo("Model Dropdown", modelNames[currentIdx]))
		{
			for (int i = 0; i < models.size(); i++)
			{
				const bool is_selected = (currentIdx == i);
				if (Selectable(modelNames[i], is_selected))
					currentIdx = i;

				if (is_selected)
				{
					SetItemDefaultFocus();
				}
			}
			setModel(models[currentIdx]);
			EndCombo();
		}

		ImGui::End();
	}

	void Game::reloadShaders(core::events::key_input& input)
	{
		if (input.action == GLFW_PRESS)
		{
			switch (input.key)
			{
			case GLFW_KEY_1:
				gfx::ShaderCache::reloadShaders();
				break;
			}
		}
	}

	void Game::move(core::events::key_input& input)
	{
		auto& transf = camera.getComponent<core::transform>();
		if (input.action == GLFW_PRESS || input.action == GLFW_REPEAT)
		{
			switch (input.key)
			{
			case GLFW_KEY_D:
			case GLFW_KEY_RIGHT:
				camPos -= math::normalize(math::cross(cameraFront, cameraUp)) * speed * deltaTime;
				break;
			case GLFW_KEY_A:
			case GLFW_KEY_LEFT:
				camPos += math::normalize(math::cross(cameraFront, cameraUp)) * speed * deltaTime;
				break;
			case GLFW_KEY_W:
			case GLFW_KEY_UP:
				camPos += speed * cameraFront * deltaTime;
				break;
			case GLFW_KEY_S:
			case GLFW_KEY_DOWN:
				camPos -= speed * cameraFront * deltaTime;
				break;
			}
		}

		transf.position = camPos;
	}

	void Game::mouselook(core::events::mouse_input& input)
	{
		if (firstMouse)
		{
			lastX = input.xpos;
			lastY = input.ypos;
			firstMouse = false;
		}

		float xoffset = lastX - input.xpos;
		float yoffset = lastY - input.ypos;
		lastX = input.xpos;
		lastY = input.ypos;

		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
		auto& camTransf = camera.getComponent<core::transform>();

		math::vec3 direction;
		direction.x = cos(math::radians(yaw)) * cos(math::radians(pitch));
		direction.y = sin(math::radians(pitch));
		direction.z = sin(math::radians(yaw)) * cos(math::radians(pitch));

		math::mat3 rotMat = math::toMat3(camTransf.rotation);
		math::vec3 right = rotMat * math::vec3::right;
		math::vec3 fwd = math::normalize(math::cross(right, math::vec3::up));
		math::vec3 up = rotMat * math::vec3::up;

		//camTransf.rotation = math::quat(math::lookAt(camPos, camPos + math::normalize(direction), up));
	}

	void Game::setModel(gfx::model_handle handle)
	{
		auto& renderer = ent.getComponent<gfx::mesh_renderer>();
		if (renderer.model != handle)
		{
			renderer.model = handle;
			renderer.dirty = true;
		}
	}

	void Game::randomShader(core::events::key_input& input)
	{
	}

	void Game::debugInfo(core::events::key_input& input)
	{
		auto& cam = camera.getComponent<gfx::camera>();
		//auto& transf = camera.getComponent<core::transform>();
		auto& entTransf = ent.getComponent<core::transform>();

		if (input.action == GLFW_PRESS)
		{
			switch (input.key)
			{
			case GLFW_KEY_T:
				log::debug("Perspective Matrix\n{}", cam.projection);
				log::debug("View Matrix\n{}", cam.view);
				log::debug("ProjeView\n{}", cam.projection * cam.view);
				log::debug("MVP\n{}", (cam.projection * cam.view) * entTransf.to_world());
				break;
			}
		}
	}
}