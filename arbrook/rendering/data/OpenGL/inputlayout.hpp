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
	private:
		window m_hwnd;
		std::vector<vertexattribute> m_vertexAttribs;
	public:

		void initialize(window& hwnd, unsigned int numBuffers, shader_handle shader)
		{
			m_hwnd = hwnd;
			glGenVertexArrays(1, &id);
		}

		void bind()
		{
			glBindVertexArray(id);

			if (m_vertexAttribs.size() > 0)
			{
				for (auto& attrib : m_vertexAttribs)
				{
					int bufId;
					glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &bufId);
					glBindVertexBuffer(attrib.inputSlot + attrib.index, bufId, attrib.offset, attrib.stride);
					glVertexAttribBinding(attrib.inputSlot + attrib.index, attrib.inputSlot);
					glEnableVertexAttribArray(attrib.inputSlot + attrib.index);

					switch (attrib.format)
					{
					case FormatType::RGB32F:
						glVertexAttribFormat(attrib.inputSlot + attrib.index, 3, static_cast<GLenum>(DataType::FLOAT), false, attrib.offset);
						break;
					case FormatType::RGBA32F:
						glVertexAttribFormat(attrib.inputSlot + attrib.index, 4, static_cast<GLenum>(DataType::FLOAT), false, attrib.offset);
						break;
					case FormatType::R32U:
						glVertexAttribFormat(attrib.inputSlot + attrib.index, 1, static_cast<GLenum>(DataType::UINT), false, attrib.offset);
						break;
					case FormatType::RG32F:
						glVertexAttribFormat(attrib.inputSlot + attrib.index, 2, static_cast<GLenum>(DataType::FLOAT), false, attrib.offset);
						break;
					default:
						log::warn("Format is not supported for vertex attributes");
						break;
					}

					switch (attrib.inputClass)
					{
					case InputClass::PER_VERTEX:
						glVertexBindingDivisor(attrib.inputSlot + attrib.index, 0);
						break;
					case InputClass::PER_INSTANCE:
						glVertexBindingDivisor(attrib.inputSlot + attrib.index, attrib.step);
						break;
					}
				}
				clearAttributes();
			}
		}

		void setAttributePtr(const std::string& attribName, unsigned int index, FormatType components, unsigned int inputSlot, unsigned int stride, unsigned int offset, InputClass inputClass, unsigned int instancedStep)
		{
			m_vertexAttribs.emplace_back(vertexattribute{ attribName.c_str(), index, components, inputSlot,stride, offset, inputClass, instancedStep });
		}

		void clearAttributes()
		{
			m_vertexAttribs.clear();
		}

		void release()
		{
			glDeleteVertexArrays(1,&id);
			clearAttributes();
		}
	};
}