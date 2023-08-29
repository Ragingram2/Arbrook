#pragma once
#include "rendering/data/model.hpp"

namespace rythe::rendering
{
	struct model_handle
	{
		model* m_data = nullptr;
		model_handle() = default;
		model_handle(std::nullptr_t null_ptr) : m_data(null_ptr) {}
		model_handle(model* data) : m_data(data) {}
		model_handle(model& data) : m_data(&data) {}

		model* operator->() { return m_data; }
		operator model& () const { return *m_data; }

		bool operator ==(std::nullptr_t null_ptr) { return m_data == nullptr; }
		bool operator !=(std::nullptr_t null_ptr) { return m_data != nullptr; }
	};
}