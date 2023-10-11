#include "sandbox/systems/game.hpp"

namespace rythe::game
{
	void Game::setup()
	{
		EventBus::bind<key_input, Game, &Game::reloadShaders>(*this);
		EventBus::bind<key_input, Game, &Game::move>(*this);
		EventBus::bind<mouse_input, Game, &Game::mouselook>(*this);
		EventBus::bind<key_input, Game, &Game::debugInfo>(*this);

		mat.m_shader = gfx::ShaderCache::createShader("default", "resources/shaders/default.shader");
		mat.m_texture = gfx::TextureCache::createTexture2D("Rythe", "resources/textures/Rythe.png");

		meshHandle = gfx::MeshCache::loadMesh("Teapot", "resources/meshes/teapot.obj");
		
		ent = createEntity("Cube");
		auto& transf = ent.addComponent<core::transform>();
		transf.scale = math::vec3(1.0f, 1.0f, 1.0f);
		transf.position = math::vec3(0.0f, 0.0f, .6f);

		auto& renderer = ent.addComponent<gfx::mesh_renderer>();
		renderer.set_material(mat);
		renderer.set_mesh(meshHandle);

		camera = createEntity("Camera");
		auto& camTransf = camera.addComponent<core::transform>();
		camTransf.position = math::vec3(0.0f, 0.0f, 0.0f);
		auto& cam = camera.addComponent<gfx::camera>();
		cam.farZ = 1000.f;
		cam.nearZ = .001f;
		cam.fov = 60.f;
	}

	void Game::update()
	{
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		auto& transf = camera.getComponent<core::transform>();
		cameraUp = transf.up();
		transf.position = camPos;
		transf.rotation = math::quat(math::lookAt(camPos, camPos + cameraFront, cameraUp));
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
		//inputVec = math::vec3(0.0f);
		if (input.action == GLFW_PRESS || input.action == GLFW_REPEAT)
		{
			switch (input.key)
			{
			case GLFW_KEY_D:
			case GLFW_KEY_RIGHT:
				//inputVec.x = -speed;
				camPos += math::normalize(math::cross(cameraFront, cameraUp)) * speed*deltaTime;
				break;
			case GLFW_KEY_A:
			case GLFW_KEY_LEFT:
				//inputVec.x = speed;
				camPos -= math::normalize(math::cross(cameraFront, cameraUp)) * speed * deltaTime;
				break;
			case GLFW_KEY_W:
			case GLFW_KEY_UP:
				//inputVec.z = -speed;
				camPos += speed * cameraFront * deltaTime;
				break;
			case GLFW_KEY_S:
			case GLFW_KEY_DOWN:
				//inputVec.z = speed;
				camPos -= speed * cameraFront * deltaTime;
				break;
			}
		}
	}

	void Game::mouselook(core::events::mouse_input& input)
	{
		if (firstMouse)
		{
			lastX = input.xpos;
			lastY = input.ypos;
			firstMouse = false;
		}

		float xoffset = input.xpos - lastX;
		float yoffset = lastY - input.ypos;
		lastX = input.xpos;
		lastY = input.ypos;

		float sensitivity = .1f;
		xoffset *= sensitivity;
		yoffset *= sensitivity;

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		math::vec3 direction;
		direction.x = cos(math::radians(yaw)) * cos(math::radians(pitch));
		direction.y = sin(math::radians(pitch));
		direction.z = sin(math::radians(yaw)) * cos(math::radians(pitch));
		cameraFront = math::normalize(direction);
	}

	void Game::debugInfo(core::events::key_input& input)
	{
		auto& cam = camera.getComponent<gfx::camera>();
		auto& transf = camera.getComponent<core::transform>();
		auto& entTransf = ent.getComponent<core::transform>();

		if (input.action == GLFW_PRESS)
		{
			switch (input.key)
			{
			case GLFW_KEY_T:
				log::debug("Perspective Matrix\n{}", cam.projection);
				log::debug("View Matrix\n{}", cam.view);
				log::debug("ProjeView\n{}", cam.projection * cam.view);
				log::debug("MVP\n{}", cam.projection * cam.view * entTransf.to_world());
				break;
			}
		}
	}
}