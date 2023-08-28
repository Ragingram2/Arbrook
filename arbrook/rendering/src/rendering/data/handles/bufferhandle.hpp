#pragma once
#include "rendering/interface/ibuffer.hpp"
#include "rendering/interface/config.hpp"
#include EnumTypes_HPP_PATH
#include Buffer_HPP_PATH

namespace rythe::rendering
{
	//struct buffer_handle
	//{
	//	Ibuffer<internal::buffer>* m_buffer = nullptr;
	//	buffer_handle() = default;
	//	buffer_handle(std::nullptr_t null_ptr) : m_buffer(null_ptr) {}
	//	buffer_handle(Ibuffer<internal::buffer>* buf) : m_buffer(buf) { }
	//	buffer_handle(buffer_handle& buf) : m_buffer(buf.m_buffer) { }

	//	Ibuffer<internal::buffer>* operator->() { return m_buffer; }
	//	operator Ibuffer<internal::buffer>& () const { return *m_buffer; }
	//	operator unsigned int() const { return m_buffer->getId(); }

	//	TargetType getTargetType() { return m_buffer->getTargetType(); }
	//};
}
