#pragma once
#include "rendering/data/config.hpp"
#include Buffer_HPP_PATH

namespace rythe::rendering
{
	struct buffer_handle
	{
		internal::buffer* m_buffer;
		buffer_handle() = default;
		buffer_handle(internal::buffer* buf) : m_buffer(buf) { }

		internal::buffer* operator->() { return m_buffer; }
		operator internal::buffer& () const { return *m_buffer; }
		operator unsigned int() const { return m_buffer->m_id; }
	};

}
