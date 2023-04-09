#pragma once
#include <memory>

#include <GL/glew.h>

#include <rythe/primitives>

#include "rendering/data/vertex.hpp"
#include "rendering/data/vertexattribute.hpp"
#include "rendering/data/config.hpp"
#include Buffer_HPP_PATH
#include EnumTypes_HPP_PATH
#include Window_HPP_PATH

namespace rythe::rendering::internal
{
	struct vertexarray
	{
	private:
		std::vector<vertexattribute> m_vertexAttribs;
	public:
		unsigned int m_id = 0;
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
			if (m_id == 0)
				initialize();

			m_hwnd = hwnd;
			glBindVertexArray(m_id);
		}

		void unbind()
		{
			glBindVertexArray(0);
		}

		void submitAttributes()
		{
			for (auto attrib : m_vertexAttribs)
			{
				glEnableVertexArrayAttrib(m_id, attrib.index);
				switch (attrib.format)
				{
				case FormatType::RGB32F:
					glVertexAttribPointer(attrib.index, 3, static_cast<GLenum>(DataType::FLOAT), false, attrib.stride, &attrib.offset);
					break;
				case FormatType::RGBA32F:
					glVertexAttribPointer(attrib.index, 4, static_cast<GLenum>(DataType::FLOAT), false, attrib.stride, &attrib.offset);
					break;
				case FormatType::R32U:
					glVertexAttribPointer(attrib.index, 1, static_cast<GLenum>(DataType::UINT), false, attrib.stride, &attrib.offset);
					break;
				case FormatType::RG32F:
					glVertexAttribPointer(attrib.index, 2, static_cast<GLenum>(DataType::FLOAT), false, attrib.stride, &attrib.offset);
					break;
				}
			}
		}

		void bufferVertexData(vertex data[], int size)
		{
			m_vertexBuffer.bufferData<vertex>(data, size);
		}

		void bufferIndexData(unsigned int data[], int size)
		{
			m_indexBuffer.bufferData<unsigned int>(data, size);
		}

		void setAttributePtr(const char* attribName, unsigned int index, FormatType components, unsigned int stride, unsigned int offset = 0)
		{
			m_vertexAttribs.emplace_back(vertexattribute{ attribName,index, components, stride, offset });
		}
	};
}