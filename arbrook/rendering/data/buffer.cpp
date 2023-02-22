#include "rendering/data/buffer.hpp"

namespace rythe::rendering
{
#pragma region Vertex buffer
	template<>
	void buffer<vertex, float>::initialize(int n)
	{
		m_type = GL_ARRAY_BUFFER;
		glGenBuffers(n, &m_id);
		bind();
	}

	//template<typename T>
	//void buffer<T>::setAttributePtr(int index, int components, GLenum type, bool normalize, const void* pointer)
	//{
	//	glEnableVertexAttribArray(index);
	//	glVertexAttribPointer(index, components, type, normalize, components * sizeof(T), pointer);
	//}

	//template<>
	//template<typename dataType>
	//void buffer<vertex>::bufferData(dataType data[], int size, unsigned int usage)
	//{
	//	m_data.insert(m_data.end(), &data[0], &data[size]);
	//	m_usage = usage;

	//	glBufferData(m_type, size, m_data.data(), m_usage);
	//}

#pragma endregion
#pragma region Index buffer
	template<>
	void buffer<index, unsigned int>::initialize(int n)
	{
		m_type = GL_ELEMENT_ARRAY_BUFFER;
		glGenBuffers(n, &m_id);
		bind();
	}
#pragma endregion
}