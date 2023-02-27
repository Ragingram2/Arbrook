#include "rendering/data/vertexarray.hpp"

namespace rythe::rendering
{
	void vertexarray::initialize(int num)
	{
		glGenVertexArrays(num, &m_id);
		bind();
		m_vertexBuffer.initialize();
		m_indexBuffer.initialize();
	}

	void vertexarray::bind()
	{
		glBindVertexArray(m_id);
	}

	void vertexarray::unbind()
	{
		glBindVertexArray(0);
	}

	void vertexarray::bufferVertexData(float data[], int size, unsigned int usage)
	{
		m_vertexBuffer.bufferData(data, size, UsageType::StaticDraw);
	}

	void vertexarray::bufferIndexData(unsigned int data[], int size, unsigned int usage)
	{
		m_indexBuffer.bufferData(data, size, UsageType::StaticDraw);
	}

	void vertexarray::setAttributePtr(int index, int components, GLenum type, bool normalize, int stride, const void* pointer)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, components, type, normalize, stride, pointer);
	}
}
