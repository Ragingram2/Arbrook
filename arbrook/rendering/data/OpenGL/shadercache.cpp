#include "rendering/data/OpenGL/shadercache.hpp"

namespace rythe::rendering::internal
{
	std::unordered_map<std::string, std::unique_ptr<shader>> ShaderCache::m_shaders;

	shader* ShaderCache::loadShader(const std::string& shaderName, const std::string& filepath)
	{
		if (m_shaders.contains(shaderName))
		{
			log::warn("Shader {} already exists, ignoring new shader, and returning existing one", shaderName);
			return m_shaders[shaderName].get();
		}

		auto source = loadSource(filepath);

		auto shdrptr = m_shaders.emplace(shaderName, std::make_unique<shader>()).first->second.get();

		shdrptr->m_name = shaderName;
		auto& programId = shdrptr->m_programId = glCreateProgram();

		unsigned int vs = compileShader(GL_VERTEX_SHADER, source.vertexSource);
		unsigned int fs = compileShader(GL_FRAGMENT_SHADER, source.fragSource);

		glAttachShader(programId, vs);
		glAttachShader(programId, fs);
		glLinkProgram(programId);
		glValidateProgram(programId);

		glDeleteShader(vs);
		glDeleteShader(fs);

		glUseProgram(programId);

		return shdrptr;
	}

	shader* ShaderCache::getShader(const std::string& shaderName)
	{
		if (m_shaders.contains(shaderName))
		{
			glUseProgram(m_shaders[shaderName]->m_programId);
			return m_shaders[shaderName].get();
		}
		log::warn("Shader {} does not exist", shaderName);
		return nullptr;
	}

	void ShaderCache::deleteShader(const std::string& shaderName)
	{

	}

	unsigned int ShaderCache::compileShader(unsigned int type, const std::string& source)
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

	shader_source ShaderCache::loadSource(const std::string& filepath)
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
}