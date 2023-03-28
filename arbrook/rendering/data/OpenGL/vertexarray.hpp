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
		buffer m_indexBuffer;
		buffer m_vertexBuffer;

		window m_hwnd;

		void initialize(int num = 1)
		{
			glGenVertexArrays(num, &m_id);
			m_vertexBuffer.initialize(TargetType::ARRAY_BUFFER, UsageType::StaticDraw);
			m_indexBuffer.initialize(TargetType::ELEMENT_ARRAY_BUFFER, UsageType::StaticDraw);
		}

		void bind(window& hwnd)
		{
			m_hwnd = hwnd;
			glBindVertexArray(m_id);
		}

		void unbind()
		{
			glBindVertexArray(0);
		}

		void bufferVertexData(float data[], int size)
		{
			m_vertexBuffer.bufferData(m_hwnd, data, size);
		}

		void bufferIndexData(unsigned int data[], int size)
		{
			m_indexBuffer.bufferData(m_hwnd, data, size);
		}

		void setAttributePtr(int index, DataType type, int stride, int components = 0, bool normalize=false, const void* pointer = 0)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, components, static_cast<GLenum>(type), normalize, stride, pointer);
		}
	};
}