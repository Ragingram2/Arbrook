#pragma once
#include <string>
#include <GL/glew.h>

#include "core/math/math.hpp"
#include "core/logging/logging.hpp"
#include "rendering/data/shadersource.hpp"

namespace rythe::rendering::internal
{
	//Put shader create stuff here
	struct shader
	{
		unsigned int m_programId;
		std::string m_name;

		shader() = default;
		shader(shader* other)
		{
			m_programId = other->m_programId;
			m_name = other->m_name;
		}
		operator unsigned int() const { return m_programId; }

		void initialize(const std::string& name, const shader_source& source)
		{
			m_name = name;
			auto& programId = m_programId = glCreateProgram();

			unsigned int vs = compileShader(GL_VERTEX_SHADER, source.vertexSource);
			unsigned int fs = compileShader(GL_FRAGMENT_SHADER, source.fragSource);

			glAttachShader(programId, vs);
			glAttachShader(programId, fs);
			glLinkProgram(programId);
			glValidateProgram(programId);

			glDeleteShader(vs);
			glDeleteShader(fs);
		}

		void setUniform(const std::string& uniformName, math::vec4 value)
		{
			int uniformPos = glGetUniformLocation(m_programId, uniformName.c_str());
			glUniform4f(uniformPos, value.x, value.y, value.z, value.w);
		}

		void setUniform(const std::string& uniformName, math::vec3 value)
		{
			int uniformPos = glGetUniformLocation(m_programId, uniformName.c_str());
			glUniform3f(uniformPos, value.x, value.y, value.z);
		}

		void setUniform(const std::string& uniformName, math::vec2 value)
		{
			int uniformPos = glGetUniformLocation(m_programId, uniformName.c_str());
			glUniform2f(uniformPos, value.x, value.y);
		}

		void setUniform(const std::string& uniformName, float value)
		{
			int uniformPos = glGetUniformLocation(m_programId, uniformName.c_str());
			glUniform1f(uniformPos, value);
		}

		void setUniform(const std::string& uniformName, math::ivec4 value)
		{
			int uniformPos = glGetUniformLocation(m_programId, uniformName.c_str());
			glUniform4i(uniformPos, value.x, value.y, value.z, value.w);
		}

		void setUniform(const std::string& uniformName, math::ivec3 value)
		{
			int uniformPos = glGetUniformLocation(m_programId, uniformName.c_str());
			glUniform3i(uniformPos, value.x, value.y, value.z);
		}

		void setUniform(const std::string& uniformName, math::ivec2 value)
		{
			int uniformPos = glGetUniformLocation(m_programId, uniformName.c_str());
			glUniform2i(uniformPos, value.x, value.y);
		}

		void setUniform(const std::string& uniformName, int value)
		{
			int uniformPos = glGetUniformLocation(m_programId, uniformName.c_str());
			glUniform1i(uniformPos, value);
		}

	private:
		unsigned int compileShader(unsigned int type, const std::string& source)
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
	};

}