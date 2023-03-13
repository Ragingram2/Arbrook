#pragma once
#include <string>

#include "core/math/math.hpp"
#include "rendering/data/textureparameters.hpp"

namespace rythe::rendering
{
	struct texture
	{
		unsigned int m_id;
		std::string m_name;
		unsigned char* m_data;
		texture_parameters m_params;
		texture() = default;
		texture(unsigned int id, std::string name) : m_id(id), m_name(name) { }
		texture(texture* other)
		{
			m_name = other->m_name;
			m_id = other->m_id;
			m_data = other->m_data;
			m_params = other->m_params;
		}
	};
}