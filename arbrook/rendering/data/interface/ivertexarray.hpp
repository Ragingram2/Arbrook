#pragma once
#include "rendering/data/interface/enumtypes.hpp"
#include "rendering/data/config.hpp"
#include EnumTypes_HPP_PATH
#include Window_HPP_PATH

namespace rythe::rendering
{
	template<typename APIType>
	struct Ivertexarray
	{
	private:
		APIType m_impl;
	public:
		void initialize(int num = 1) { m_impl.initialize(num); }

		void bind(internal::window& hwnd) { m_impl.bind(hwnd); }

		void unbind() { m_impl.unbind(); }

		void bufferVertexData(float data[], int size) { m_impl.bufferVertexData(data, size); }

		void bufferIndexData(unsigned int data[], int size) { m_impl.bufferIndexData(data, size); }

		void setAttributePtr(int index, int components, DataType type, bool normalize, int stride, const void* pointer = 0) { m_impl.setAttributePtr(index, components, static_cast<internal::DataType>(type), normalize, stride, pointer); }
	};
}