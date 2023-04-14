#pragma once
#include "rendering/data/interface/ibuffer.hpp"
#include "rendering/data/config.hpp"
#include EnumTypes_HPP_PATH
#include Buffer_HPP_PATH

namespace rythe::rendering
{
	struct buffer_handle
	{
		Ibuffer<internal::buffer>* buffer = nullptr;
		buffer_handle() = default;
		buffer_handle(Ibuffer<internal::buffer>* buf) : buffer(buf) { }

		Ibuffer<internal::buffer>* operator->() { return buffer; }
		operator Ibuffer<internal::buffer>& () const { return *buffer; }
		operator unsigned int() const { return buffer->getId(); }

		TargetType getTargetType() { return buffer->getTargetType(); }
	};
}
