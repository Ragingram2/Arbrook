#include "rendering/systems/rendersystem.hpp"

namespace rythe::rendering
{
	//void GLAPIENTRY MessageCallback(GLenum source,
	//	GLenum type,
	//	GLuint id,
	//	GLenum severity,
	//	GLsizei length,
	//	const GLchar* message,
	//	const void* userParam)
	//{
	//	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
	//		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
	//		type, severity, message);
	//}

	void Renderer::setup()
	{
		log::info("Initializing Render System");
		if (!glfwInit())
			return;
		m_window.initialize(math::ivec2(600, 600), "Arbrook");

		if (!m_window)
		{
			glfwTerminate();
			log::error("Window initialization failed");
			return;
		}

		window::makeCurrent();

		if (glewInit() != GLEW_OK)
		{
			log::error("Something whent wrong when initializing GLEW");
			return;
		}

		//glEnable(GL_DEBUG_OUTPUT);
		//glDebugMessageCallback(MessageCallback, 0);

		auto& defaultShader = createShader("default", "resources/shaders/default.shader");
		defaultShader.initialize();
	}

	void Renderer::update()
	{
		window::makeCurrent();

		m_window.setSwapInterval(1);

		if (m_window.shouldClose())
		{
			rythe::core::events::exit evnt(0);
			raiseEvent(evnt);
			return;
		}

		glClear(GL_COLOR_BUFFER_BIT);

		for (auto& ent : m_filter)
		{
			auto& renderComp = ent.getComponent<shape_renderer>();
			renderComp.indexBuffer.bind();
			renderComp.vertexBuffer.bind();

			auto& transf = ent.getComponent<core::transform>();

			auto& shader = getShader("default");
			shader.setUniform("u_position", transf.position);
			shader.setUniform("u_color", math::vec4(r, .5f - (r / 2.0f), 1.f - r, 1.f));
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

			renderComp.indexBuffer.unbind();
			renderComp.vertexBuffer.unbind();
		}

		if (r > 1.0f)
			inc = -0.05f;
		else if (r < 0.0f)
			inc = 0.05f;

		r += inc;

		m_window.swapBuffers();

		m_window.pollEvents();
	}

	void Renderer::shutdown()
	{
		glfwTerminate();
	}

	shader& Renderer::createShader(const std::string& name, const std::string& filePath)
	{
		if (m_shaders.contains(name))
		{
			log::warn("Shader \"" + std::string(name) + "\" already exists, returning a reference to that one");
			return m_shaders[name];
		}

		shader defaultShader(filePath);
		m_shaders.emplace(name, defaultShader);
		return m_shaders[name];
	}

	shader& Renderer::getShader(const std::string& name)
	{
		return m_shaders[name];
	}

	void Renderer::clearLog()
	{
		while (glGetError() != GL_NO_ERROR);
	}

	bool Renderer::logCall()
	{
		bool success = true;
		while (GLenum error = glGetError())
		{
			log::error(error);
			__debugbreak();
			success = false;
		}
		return success;
	}
}