#include "rendering/systems/rendersystem.hpp"

namespace rythe::rendering
{
	void Renderer::setup()
	{
		log::debug("Render System setup");
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

		float positions[] =
		{
			-0.5f, -0.5f,//0
			 0.5f, -0.5f,//1
			 0.5f,  0.5f,//2
			-0.5f, 0.5f //3
		};

		float colors[] =
		{
			1.0f, 0.0f,0.0f,1.0f,//0
			0.0f, 1.0f,0.0f,1.0f,//1
			0.0f, 0.0f,1.0f,1.0f,//2
			1.0f, 1.0f,0.0f,1.0f//3
		};

		unsigned int indicies[] =
		{
			0,1,2,
			2,3,0
		};

		//Vertex  buffer
		{
			unsigned int positionBuffer;
			glGenBuffers(1, &positionBuffer);
			glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
		}

		////Color buffer
		//{
		//	unsigned int colorBuffer;
		//	glGenBuffers(1, &colorBuffer);
		//	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		//	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
		//	glEnableVertexAttribArray(0);
		//	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		//}

		//index  buffer
		{
			unsigned int ibo;
			glGenBuffers(1, &ibo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indicies, GL_STATIC_DRAW);
		}

		shader_source source = parseShader("resources/shaders/default.shader");
		unsigned int shader = createShader(source.vertexSource, source.fragSource);
		glUseProgram(shader);

		loc = glGetUniformLocation(shader, "u_color");

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
		//clearErrors();
		glUniform4f(loc, r, 0.3f, .8f, 1.0f);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		if (r > 1.0f)
		{
			inc = -0.05f;
		}
		else if (r < 0.0f)
		{
			inc = 0.05f;
		}

		r += inc;

		logCall();
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	void Renderer::shutdown()
	{
		glfwTerminate();
	}

	unsigned int Renderer::createShader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		unsigned int program = glCreateProgram();
		unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
		unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}

	unsigned int Renderer::compileShader(unsigned int type, const std::string& source)
	{
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);

		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)__builtin_alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);

		if (result == GL_FALSE)
		{
			log::error(message);
			glDeleteShader(id);
			return 0;
		}

		return id;
	}

	shader_source Renderer::parseShader(const std::string& filepath)
	{
		std::ifstream stream(filepath);

		enum class ShaderType
		{
			NONE = -1,
			VERTEX = 0,
			FRAG = 1
		};


		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;
		while (getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
				{
					type = ShaderType::VERTEX;
				}
				else if (line.find("fragment") != std::string::npos)
				{
					type = ShaderType::FRAG;
				}
			}
			else
			{
				ss[(int)type] << line << "\n";
			}
		}

		return { ss[0].str(),ss[1].str() };
	}

	void Renderer::clearErrors()
	{
		while (glGetError() != GL_NO_ERROR);

	}

	bool Renderer::logCall()
	{
		while (GLenum error = glGetError())
		{
			log::error(error);
			return false;
		}
		return true;
	}
}