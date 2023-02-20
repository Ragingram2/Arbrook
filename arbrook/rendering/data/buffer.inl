#include "rendering/data/buffer.hpp"
#pragma once

namespace rythe::rendering
{
	template<typename T>
	void buffer<T>::initialize(GLenum type, GLsizei n = 1)
	{
		m_type = type;
		glGenBuffers(n, &m_id);
		bind();
	}

	template<typename T>
	void buffer<T>::bind()
	{
		glBindBuffer(m_type, m_id);
	}

	template<typename T>
	void buffer<T>::unbind()
	{
		glBindBuffer(m_type, 0);
	}

	template<typename T>
	void buffer<T>::bufferData(T data[], int size, GLenum usage)
	{
		m_data.insert(m_data.end(), &data[0], &data[size]);
		m_usage = usage;

		glBufferData(m_type, size, m_data.data(), m_usage);
	}

	template<typename T>
	void buffer<T>::setAttributePtr(int index, int components, GLenum type, bool normalize, const void* pointer = 0)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, components, type, normalize, components * sizeof(T), pointer);
	}
}