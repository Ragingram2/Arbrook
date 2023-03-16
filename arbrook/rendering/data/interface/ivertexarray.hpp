#pragma once
#include "rendering/data/interface/enumtypes.hpp"
#include "rendering/data/config.hpp"
#include EnumTypes_HPP_PATH

namespace rythe::rendering
{
	template<typename APIType>
	struct Ivertexarray
	{
	private:
		APIType m_impl;
	public:
		void initialize(int num = 1) { m_impl.initialize(num); }

		void bind() { m_impl.bind(); }

		void unbind() { m_impl.unbind(); }

		void bufferVertexData(float data[], int size, UsageType usage) { m_impl.bufferVertexData(data, size, static_cast<internal::UsageType>(usage)); }

		void bufferIndexData(unsigned int data[], int size, UsageType usage) { m_impl.bufferIndexData(data, size, static_cast<internal::UsageType>(usage)); }

		void setAttributePtr(int index, int components, DataType type, bool normalize, int stride, const void* pointer = 0) { m_impl.setAttributePtr(index, components, static_cast<internal::DataType>(type), normalize, stride, pointer); }
	};
}