#include "rendering/data/shader.hpp"

namespace rythe::rendering
{
	namespace log = core::log;
	shader::shader(const std::string& filepath) 
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
		m_vertexSource = ss[0].str();
		m_fragSource = ss[1].str();
	}

	void shader::initialize()
	{
		m_programId = glCreateProgram();
		unsigned int vs = compileShader(GL_VERTEX_SHADER, m_vertexSource);
		unsigned int fs = compileShader(GL_FRAGMENT_SHADER, m_fragSource);

		glAttachShader(m_programId, vs);
		glAttachShader(m_programId, fs);
		glLinkProgram(m_programId);
		glValidateProgram(m_programId);

		glDeleteShader(vs);
		glDeleteShader(fs);

		glUseProgram(m_programId);
	}

	unsigned int shader::compileShader(unsigned int type, const std::string& source)
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

	bool shader::registerUniform(const std::string& name)
	{
		glUseProgram(m_programId);
		if (!m_uniforms.contains(name))
		{
			auto loc = glGetUniformLocation(m_programId, name.c_str());
			if (loc != -1)
			{
				m_uniforms.emplace(name, loc);
				return true;
			}
			return false;
		}
		return true;
	}

	template<>
	void shader::setUniform(const std::string& name, int value)
	{
		if (registerUniform(name))
			glUniform1i(m_uniforms[name], value);
	}

	template<>
	void shader::setUniform(const std::string& name, math::ivec2 value)
	{
		if (registerUniform(name))
			glUniform2i(m_uniforms[name], value.x, value.y);
	}

	template<>
	void shader::setUniform(const std::string& name, math::ivec3 value)
	{
		if (registerUniform(name))
			glUniform3i(m_uniforms[name], value.x, value.y, value.z);
	}

	template<>
	void shader::setUniform(const std::string& name, math::ivec4 value)
	{
		if (registerUniform(name))
			glUniform4i(m_uniforms[name], value.x, value.y, value.z, value.w);
	}

	template<>
	void shader::setUniform(const std::string& name, float value)
	{
		if (registerUniform(name))
			glUniform1f(m_uniforms[name], value);
	}

	template<>
	void shader::setUniform(const std::string& name, math::vec2 value)
	{
		if (registerUniform(name))
			glUniform2f(m_uniforms[name], value.x, value.y);
	}

	template<>
	void shader::setUniform(const std::string& name, math::vec3 value)
	{
		if (registerUniform(name))
			glUniform3f(m_uniforms[name], value.x, value.y, value.z);
	}

	template<>
	void shader::setUniform(const std::string& name, math::vec4 value)
	{
		if (registerUniform(name))
			glUniform4f(m_uniforms[name], value.x, value.y, value.z, value.w);
	}
}