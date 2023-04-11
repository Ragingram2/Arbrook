#pragma once
#include "rendering/data/vertex.hpp"
#include "rendering/data/bufferhandle.hpp"
#include "rendering/data/shaderhandle.hpp"
#include "rendering/data/interface/enumtypes.hpp"
#include "rendering/data/config.hpp"
#include EnumTypes_HPP_PATH
#include Window_HPP_PATH

namespace rythe::rendering
{
	template<typename APIType>
	struct Iinputlayout
	{
	private:
		APIType m_impl;
	public:
		void bind(internal::window& hwnd, shader_handle shader) { m_impl.bind(hwnd, shader); }

		void unbind() { m_impl.unbind(); }

		void addBuffer(buffer_handle handle) { m_impl.addBuffer(handle); }

		void submitAttributes() { m_impl.submitAttributes(); }

		void setAttributePtr(const std::string& attribName, unsigned int index, FormatType components, unsigned int stride, unsigned int offset) { m_impl.setAttributePtr(attribName, index, static_cast<internal::FormatType>(components), stride, offset); }
	};
}