#pragma once
#include "rendering/interface/ishader.hpp"
#include "rendering/interface/config.hpp"
#include Shader_HPP_PATH

namespace rythe::rendering
{
	//struct shader_handle
	//{
	//	Ishader<internal::shader>* m_shader = nullptr;
	//	shader_handle() = default;
	//	shader_handle(std::nullptr_t null_ptr) : m_shader(null_ptr) {}
	//	shader_handle(Ishader<internal::shader>* shad) : m_shader(shad) { }
	//	shader_handle(shader_handle& shad) : m_shader(shad.m_shader) { }

	//	Ishader<internal::shader>* operator->() { return m_shader; }
	//	operator Ishader<internal::shader>& () const { return *m_shader; }
	//	operator unsigned int() const { return m_shader->getId(); }

	//	bool operator ==(std::nullptr_t null_ptr) { return m_shader == nullptr; }
	//	bool operator !=(std::nullptr_t null_ptr) { return m_shader != nullptr; }
	//};
}