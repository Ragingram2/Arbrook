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
			glGenVertexArrays(numBuffers, &id);
		}

		void bind()
		{
			if (m_vertexAttribs.size() > 0)
			{
				for (auto& attrib : m_vertexAttribs)
				{
					glEnableVertexAttribArray(attrib.index);
					switch (attrib.format)
					{
					case FormatType::RGB32F:
						glVertexAttribPointer(attrib.index, 3, static_cast<GLenum>(DataType::FLOAT), false, attrib.stride, reinterpret_cast<void*>(attrib.offset));
						break;
					case FormatType::RGBA32F:
						glVertexAttribPointer(attrib.index, 4, static_cast<GLenum>(DataType::FLOAT), false, attrib.stride, reinterpret_cast<void*>(attrib.offset));
						break;
					case FormatType::R32U:
						glVertexAttribPointer(attrib.index, 1, static_cast<GLenum>(DataType::UINT), false, attrib.stride, reinterpret_cast<void*>(attrib.offset));
						break;
					case FormatType::RG32F:
						glVertexAttribPointer(attrib.index, 2, static_cast<GLenum>(DataType::FLOAT), false, attrib.stride, reinterpret_cast<void*>(attrib.offset));
						break;
					default:
						log::warn("Format is not supported for vertex attributes");
						break;
					}

					switch (attrib.inputClass)
					{
					case InputClass::PER_VERTEX:
						glVertexAttribDivisor(attrib.index, 0);
						break;
					case InputClass::PER_INSTANCE:
						glVertexAttribDivisor(attrib.index, 1);
						break;
					}
				}
				clearAttributes();
			}

			glBindVertexArray(id);
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
			clearAttributes();
		}
	};
}