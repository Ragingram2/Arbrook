#pragma once
#include <string>

namespace rythe::rendering
{
	struct shader
	{
	public:
		unsigned int m_programId;
		std::string m_name;

		shader() = default;
		shader(shader* other)
		{
			m_programId = other->m_programId;
			m_name = other->m_name;
		}
		operator unsigned int() const { return m_programId; }
	};

}