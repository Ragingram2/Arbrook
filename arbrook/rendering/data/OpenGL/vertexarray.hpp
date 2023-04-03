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
			m_vertexBuffer.bufferData<float, float>(m_hwnd, data, size);
		}

		void bufferIndexData(unsigned int data[], int size)
		{
			m_indexBuffer.bufferData<unsigned int, unsigned int>(m_hwnd, data, size);
		}

		void setAttributePtr(std::string attribName, unsigned int index, FormatType components, int stride, unsigned int offset = 0)
		{
			glEnableVertexAttribArray(index);
			glBindAttribLocation(0, index, attribName.c_str());
			switch (components)
			{
			case FormatType::RGB32F:
				glVertexAttribPointer(index, 3, static_cast<GLenum>(DataType::FLOAT), false, stride, &offset);
				break;
			case FormatType::RGBA32F:
				glVertexAttribPointer(index, 4, static_cast<GLenum>(DataType::FLOAT), false, stride, &offset);
				break;
			case FormatType::R32U:
				glVertexAttribPointer(index, 1, static_cast<GLenum>(DataType::UINT), false, stride, &offset);
				break;
			}
		}
	};
}