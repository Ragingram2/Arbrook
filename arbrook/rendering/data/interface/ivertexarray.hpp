#pragma once

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

		void bufferVertexData(float data[], int size, unsigned int usage) { m_impl.bufferVertexData(data, size, usage); }

		void bufferIndexData(unsigned int data[], int size, unsigned int usage) { m_impl.bufferIndexData(data, size, usage); }

		void setAttributePtr(int index, int components, unsigned int type, bool normalize, int stride, const void* pointer = 0) { m_impl.setAttributePtr(index, components, type, normalize, stride, pointer); }
	};
}