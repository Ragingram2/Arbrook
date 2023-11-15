#include "sandbox/systems/modelviewer.hpp"

namespace rythe::game
{
	void ModelViewer::setup()
	{
		log::debug("Initializing Game system");
		EventBus::bind<key_input, ModelViewer, &ModelViewer::reloadShaders>(*this);
		EventBus::bind<key_input, ModelViewer, &ModelViewer::move>(*this);
		EventBus::bind<key_input, ModelViewer, &ModelViewer::debugInfo>(*this);
		EventBus::bind<key_input, ModelViewer, &ModelViewer::randomShader>(*this);
		EventBus::bind<mouse_input, ModelViewer, &ModelViewer::mouselook>(*this);

		gfx::gui_stage::addGuiRender<ModelViewer, &ModelViewer::guiRender>(this);

		gfx::ModelCache::loadModels("resources/meshes/");
		gfx::TextureCache::loadTextures("resources/textures/");
		gfx::ShaderCache::loadShaders("resources/shaders/");
		modelHandle = gfx::ModelCache::getModel("cube");

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

	void ModelViewer::update()
	{
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}

	void ModelViewer::guiRender()
	{
		using namespace ImGui;
		Begin("Change Model");
		auto models = gfx::ModelCache::getModels();
		auto modelNames = gfx::ModelCache::getModelNamesC();
		ShowDemoWindow();
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

		ImGui::End();
	}

	void ModelViewer::reloadShaders(core::events::key_input& input)
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

	void ModelViewer::move(core::events::key_input& input)
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

	void ModelViewer::mouselook(core::events::mouse_input& input)
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

	void ModelViewer::setModel(gfx::model_handle handle)
	{
		auto& renderer = ent.getComponent<gfx::mesh_renderer>();
		if (renderer.model != handle)
		{
			renderer.model = handle;
			renderer.dirty = true;
		}
	}

	void ModelViewer::randomShader(core::events::key_input& input)
	{
	}

	void ModelViewer::debugInfo(core::events::key_input& input)
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