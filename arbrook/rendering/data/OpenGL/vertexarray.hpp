#pragma once
#include <memory>

#include <GL/glew.h>

#include <rythe/primitives>

#include "rendering/data/config.hpp"
#include Buffer_HPP_PATH
#include EnumTypes_HPP_PATH

namespace rythe::rendering::internal
{
	struct vertexarray
	{
		unsigned int m_id;
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

		void bufferVertexData(float data[], int size, UsageType usage)
		{
			m_vertexBuffer.bufferData(data, size, usage);
		}

		void bufferIndexData(unsigned int data[], int size, UsageType usage)
		{
			m_indexBuffer.bufferData(data, size, usage);
		}

		void setAttributePtr(int index, int components, DataType type, bool normalize, int stride, const void* pointer = 0)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, components, static_cast<GLenum>(type), normalize, stride, pointer);
		}
	};
}