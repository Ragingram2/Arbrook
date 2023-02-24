#include "rendering/data/buffer.hpp"

namespace rythe::rendering
{
#pragma region Vertex buffer
	template<>
	void buffer<vertex, float>::initialize()
	{
		m_type = GL_ARRAY_BUFFER;
		glGenBuffers(m_numBuffers, &m_id);
		bind();
	}
#pragma endregion
#pragma region Index buffer
	template<>
	void buffer<index, unsigned int>::initialize()
	{
		m_type = GL_ELEMENT_ARRAY_BUFFER;
		glGenBuffers(m_numBuffers, &m_id);
		bind();
	}
#pragma endregion
}