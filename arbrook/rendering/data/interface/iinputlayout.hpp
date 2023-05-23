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

		void addBuffer(buffer_handle handle) { m_impl.addBuffer(handle); }

		void clearBuffers() { m_impl.clearBuffers(); }

		void submitAttributes() { m_impl.submitAttributes(); }

		void setAttributePtr(const std::string& attribName, unsigned int index, FormatType components, unsigned int inputSlot, unsigned int stride, unsigned int offset, InputClass inputClass = InputClass::PER_VERTEX, unsigned int instanceStep = 0) { m_impl.setAttributePtr(attribName, index, static_cast<internal::FormatType>(components), inputSlot, stride, offset, static_cast<internal::InputClass>(inputClass), instanceStep); }

		void clearAttributes() { m_impl.clearAttributes(); }

		void release() { m_impl.release(); }
	};
}