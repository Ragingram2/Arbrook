#pragma once
#include "rendering/data/config.hpp"
#include Shader_HPP_PATH

namespace rythe::rendering
{
	struct shader_handle
	{
		internal::shader* m_shader;
		shader_handle() = default;
		shader_handle(internal::shader* shad) : m_shader(shad) { }

		internal::shader* operator->() { return m_shader; }
		operator internal::shader& () const { return *m_shader; }
		operator unsigned int() const { return m_shader->m_programId; }
	};
}