#include "rendering/systems/rendersystem.hpp"

namespace rythe::rendering
{
	void GLAPIENTRY MessageCallback(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam)
	{
		fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
			(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
			type, severity, message);
	}

	void Renderer::setup()
	{
		log::info("Initializing Render System");
		if (!glfwInit())
			return;

		window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			log::error("Window initialization failed");
			return;
		}

		glfwMakeContextCurrent(window);

		if (glewInit() != GLEW_OK)
		{
			log::error("Something whent wrong when initializing GLEW");
			return;
		}

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(MessageCallback, 0);

		//float positions[] =
		//{
		//	-0.5f, -0.5f,//0
		//	 0.5f, -0.5f,//1
		//	 0.5f,  0.5f,//2
		//	-0.5f, 0.5f //3
		//};

		//unsigned int indicies[] =
		//{
		//	0,1,2,
		//	2,3,0
		//};

		////vertex  buffer
		//{
		//	buffer<float> posBuffer(GL_ARRAY_BUFFER);
		//	posBuffer.bufferData(positions, sizeof(positions), GL_STATIC_DRAW);
		//	posBuffer.setAttributePtr(0, 2, GL_FLOAT, false);
		//}

		////index  buffer
		//{
		//	buffer<unsigned int> indexBuffer(GL_ELEMENT_ARRAY_BUFFER);
		//	indexBuffer.bufferData(indicies, sizeof(indicies), GL_STATIC_DRAW);
		//}

		auto& defaultShader = createShader("default", "resources/shaders/default.shader");
		defaultShader.initialize();
	}

	void Renderer::update()
	{
		glfwMakeContextCurrent(window);

		glfwSwapInterval(1);

		if (glfwWindowShouldClose(window))
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

		glfwSwapBuffers(window);

		glfwPollEvents();
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