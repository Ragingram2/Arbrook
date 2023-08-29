#pragma once
#include "rendering/interface/ibuffer.hpp"
#include "rendering/interface/config.hpp"
#include Buffer_HPP_PATH

namespace rythe::rendering
{
	struct buffer_handle
	{
		Ibuffer<internal::buffer>* m_data = nullptr;
		buffer_handle() = default;
		buffer_handle(std::nullptr_t null_ptr) : m_data(null_ptr) {}
		buffer_handle(Ibuffer<internal::buffer>* data) : m_data(data) {}
		buffer_handle(Ibuffer<internal::buffer>& data) : m_data(&data) {}

		Ibuffer<internal::buffer>* operator->() { return m_data; }
		operator Ibuffer<internal::buffer>& () const { return *m_data; }

		bool operator ==(std::nullptr_t null_ptr) { return m_data == nullptr; }
		bool operator !=(std::nullptr_t null_ptr) { return m_data != nullptr; }
	};
}