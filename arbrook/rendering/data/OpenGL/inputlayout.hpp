#pragma once
#include <memory>

#include <GL/glew.h>

#include <rythe/primitives>

#include "core/logging/logging.hpp"
#include "rendering/data/shaderhandle.hpp"
#include "rendering/data/bufferhandle.hpp"
#include "rendering/data/vertex.hpp"
#include "rendering/data/vertexattribute.hpp"
#include "rendering/data/config.hpp"
#include Buffer_HPP_PATH
#include EnumTypes_HPP_PATH
#include Window_HPP_PATH

namespace rythe::rendering::internal
{
	struct inputlayout
	{
	public:
		unsigned int id;
		bool initialized = false;
	private:
		window m_hwnd;
		std::vector<buffer_handle> m_vertexBuffers;
		buffer_handle m_indexBuffer;
		std::vector<vertexattribute> m_vertexAttribs;
	public:
		void bind(window& hwnd, shader_handle shader)
		{
			m_hwnd = hwnd;
			if (!initialized)
			{
				glGenVertexArrays(m_vertexBuffers.size(), &id);

				glBindVertexArray(0);
				glBindVertexArray(id);
				for (auto& handle : m_vertexBuffers)
				{
					handle->initialize(TargetType::ARRAY_BUFFER, UsageType::StaticDraw);
				}
				m_indexBuffer->initialize(TargetType::ELEMENT_ARRAY_BUFFER, UsageType::StaticDraw);
				initialized = true;
				return;
			}

			glBindVertexArray(0);
			glBindVertexArray(id);
			log::debug("Input layout bound");
			for (auto& handle : m_vertexBuffers)
			{
				handle->bind();
			}
			m_indexBuffer->bind();
		}

		void addBuffer(buffer_handle handle)
		{
			switch (handle.getTargetType())
			{
			case TargetType::ARRAY_BUFFER:
				m_vertexBuffers.push_back(handle);
				break;
			case TargetType::ELEMENT_ARRAY_BUFFER:
				m_indexBuffer = handle;
				break;
			default:
				log::error("That type is not supported");
				break;
			}
		}

		void setAttributePtr(const std::string& attribName, unsigned int index, FormatType components, unsigned int stride, unsigned int offset = 0)
		{
			m_vertexAttribs.emplace_back(vertexattribute{ attribName.c_str(), index, components, stride, offset });
		}

		void submitAttributes()
		{
			for (auto& attrib : m_vertexAttribs)
			{
				glEnableVertexArrayAttrib(id, attrib.index);
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
	};
}