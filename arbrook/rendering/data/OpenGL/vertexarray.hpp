#pragma once
#include <memory>

#include <GL/glew.h>

#include <rythe/primitives>

#include "rendering/data/OpenGL/buffer.hpp"

namespace rythe::rendering::internal
{
	enum UsageType
	{
		StaticDraw = GL_STATIC_DRAW,
	};

	struct vertexarray
	{
		GLuint m_id;
		buffer<index, unsigned int> m_indexBuffer;
		buffer<vertex, float> m_vertexBuffer;

		void initialize(int num = 1)
		{
			glGenVertexArrays(num, &m_id);
			bind();
			m_vertexBuffer.initialize();
			m_indexBuffer.initialize();
		}

		void bind()
		{
			glBindVertexArray(m_id);
		}

		void unbind()
		{
			glBindVertexArray(0);
		}

		void bufferVertexData(float data[], int size, unsigned int usage)
		{
			m_vertexBuffer.bufferData(data, size, UsageType::StaticDraw);
		}

		void bufferIndexData(unsigned int data[], int size, unsigned int usage)
		{
			m_indexBuffer.bufferData(data, size, UsageType::StaticDraw);
		}

		void setAttributePtr(int index, int components, GLenum type, bool normalize, int stride, const void* pointer = 0)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, components, type, normalize, stride, pointer);
		}
	};
}