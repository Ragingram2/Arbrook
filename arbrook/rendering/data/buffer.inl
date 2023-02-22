#include "rendering/data/buffer.hpp"
#pragma once

namespace rythe::rendering
{
	//template<typename T>
	//void buffer<T>::initialize(GLsizei n)
	//{
	//	//m_type = type;
	//	//glGenBuffers(n, &m_id);
	//	//bind();
	//}

	template<typename T, typename dataType>
		requires validType<T>
	void buffer<T, dataType>::bind()
	{
		glBindBuffer(m_type, m_id);
	}

	template<typename T, typename dataType>
		requires validType<T>
	void buffer<T, dataType>::unbind()
	{
		glBindBuffer(m_type, 0);
	}

	template<typename T, typename dataType>
		requires validType<T>
	void buffer<T, dataType>::bufferData(dataType data[], int size, unsigned int usage)
	{
		m_data.insert(m_data.end(), &data[0], &data[size]);
		m_usage = usage;

		glBufferData(m_type, size, m_data.data(), m_usage);
	}

	template<typename T, typename dataType>
		requires validType<T>
	void buffer<T, dataType>::setAttributePtr(int index, int components, GLenum type, bool normalize, const void* pointer)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, components, type, normalize, components * sizeof(T), pointer);
	}

	//template<>
	//template<typename dataType>
	//void buffer<vertex>::bufferData(dataType data[], int size, unsigned int usage)
	//{
	//	m_data.insert(m_data.end(), &data[0], &data[size]);
	//	m_usage = usage;

	//	glBufferData(m_type, size, m_data.data(), m_usage);
	//}

	//template<>
	//template<typename dataType>
	//void buffer<index>::bufferData(dataType data[], int size, unsigned int usage)
	//{
	//	m_data.insert(m_data.end(), &data[0], &data[size]);
	//	m_usage = usage;

	//	glBufferData(m_type, size, m_data.data(), m_usage);
	//}
}