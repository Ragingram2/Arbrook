#pragma once
#include "rendering/data/config.hpp"
#include EnumTypes_HPP_PATH
#include Buffer_HPP_PATH

namespace rythe::rendering
{
	struct buffer_handle
	{
		internal::buffer* buffer = nullptr;
		buffer_handle() = default;
		buffer_handle(internal::buffer* buf) : buffer(buf) { }

		internal::buffer* operator->() { return buffer; }
		operator internal::buffer& () const { return *buffer; }
		operator unsigned int() const { return buffer->id; }

		internal::TargetType getTargetType() { return buffer->m_target; }
	};
}
