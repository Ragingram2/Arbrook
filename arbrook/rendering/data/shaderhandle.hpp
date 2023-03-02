#pragma once
#include "rendering/data/shader.hpp"

namespace rythe::rendering
{
	struct shader_handle
	{
		shader* m_shader;
		shader_handle() = default;
		shader_handle(shader* shad) : m_shader(shad) { }

		shader* operator->() { return m_shader; }
		operator shader& () const { return *m_shader; }
		operator unsigned int() const { return m_shader->m_programId; }
	};
}