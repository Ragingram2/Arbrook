#pragma once
#include "rendering/data/model.hpp"
#include "rendering/interface/ishader.hpp"
#include "rendering/interface/itexture.hpp"
#include "rendering/interface/ibuffer.hpp"
#include "rendering/interface/config.hpp"
#include Shader_HPP_PATH
#include Texture_HPP_PATH
#include Buffer_HPP_PATH

namespace rythe::rendering
{
	template<typename dataType>
	struct data_handle
	{
		dataType* m_data = nullptr;
		data_handle() = default;
		data_handle(std::nullptr_t null_ptr) : m_data(null_ptr) {}
		data_handle(dataType* data) : m_data(data) {}
		data_handle(dataType& data) : m_data(data) {}

		dataType* operator->() { return m_data; }
		operator dataType& () const { return *m_data; }

		bool operator ==(std::nullptr_t null_ptr) { return m_data == nullptr; }
		bool operator !=(std::nullptr_t null_ptr) { return m_data != nullptr; }
	};

	using shader_handle = data_handle<Ishader<internal::shader>>;
	using buffer_handle = data_handle<Ibuffer<internal::buffer>>;
	using texture_handle = data_handle<Itexture<internal::texture>>;
	using model_handle = data_handle<model>;
}