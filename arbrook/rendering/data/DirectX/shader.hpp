#pragma once

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

		}

		void setUniform(const std::string& uniformName, math::vec3 value)
		{

		}

		void setUniform(const std::string& uniformName, math::vec2 value)
		{

		}

		void setUniform(const std::string& uniformName, float value)
		{

		}

		void setUniform(const std::string& uniformName, math::ivec4 value)
		{

		}

		void setUniform(const std::string& uniformName, math::ivec3 value)
		{

		}

		void setUniform(const std::string& uniformName, math::ivec2 value)
		{

		}

		void setUniform(const std::string& uniformName, int value)
		{

		}
	};
}