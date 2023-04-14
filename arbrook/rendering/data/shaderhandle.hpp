#pragma once
#include "rendering/data/interface/ishader.hpp"
#include "rendering/data/config.hpp"
#include Shader_HPP_PATH

namespace rythe::rendering
{
	struct shader_handle
	{
		Ishader<internal::shader>* m_shader = nullptr;
		shader_handle() = default;
		shader_handle(Ishader<internal::shader>* shad) : m_shader(shad) { }

		Ishader<internal::shader>* operator->() { return m_shader; }
		operator Ishader<internal::shader>& () const { return *m_shader; }
		operator unsigned int() const { return m_shader->getId(); }
	};
}