#pragma once
#include <string>
#include <GL/glew.h>

#include "core/math/math.hpp"

namespace rythe::rendering::internal
{
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
	};

}