#pragma once
#include "rendering/interface/ishader.hpp"
#include "rendering/interface/config.hpp"
#include Shader_HPP_PATH

namespace rythe::rendering
{
	struct shader_handle
	{
		Ishader<internal::shader>* m_data = nullptr;
		shader_handle() = default;
		shader_handle(std::nullptr_t null_ptr) : m_data(null_ptr) {}
		shader_handle(Ishader<internal::shader>* data) : m_data(data) {}
		shader_handle(Ishader<internal::shader>& data) : m_data(&data) {}

		Ishader<internal::shader>* operator->() { return m_data; }
		operator Ishader<internal::shader >& () const { return *m_data; }

		bool operator ==(std::nullptr_t null_ptr) { return m_data == nullptr; }
		bool operator !=(std::nullptr_t null_ptr) { return m_data != nullptr; }
	};
}