#pragma once
#include <memory>
#include <set>
#include <algorithm>

#include <GL/glew.h>

#include <rsl/primitives>

#include "core/logging/logging.hpp"
#include "rendering/data/handles/shaderhandle.hpp"
#include "rendering/data/handles/bufferhandle.hpp"
#include "rendering/data/vertex.hpp"
#include "rendering/data/vertexattribute.hpp"
#include "rendering/interface/config.hpp"
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
		std::unordered_map<unsigned int, vertexattribute> m_vertexAttribs;
		std::unordered_map<int, std::set<int>> m_flatIndeces;
	public:

		void initialize(window& hwnd, unsigned int numBuffers, shader_handle shader)
		{
			m_hwnd = hwnd;
			glGenVertexArrays(1, &id);
		}

		void bind()
		{
			glBindVertexArray(id);
		}

		void setAttributePtr(buffer_handle buf, const std::string& attribName, unsigned int index, FormatType components, unsigned int inputSlot, unsigned int stride, unsigned int offset, InputClass inputClass, unsigned int instancedStep)
		{
			m_vertexAttribs.emplace(buf->getId(), vertexattribute{ attribName.c_str(), index, components, inputSlot,stride, offset, inputClass, instancedStep });
			m_flatIndeces[inputSlot].insert(index);
		}

		void submitAttributes()
		{
			glBindVertexArray(id);
			if (m_vertexAttribs.size() > 0)
			{
				for (auto& [id, attrib] : m_vertexAttribs)
				{
					//glBindVertexBuffer(m_vertexAttribs.begin()->second.inputSlot, id, 0, m_vertexAttribs.begin()->second.stride);
					glBindBuffer(GL_ARRAY_BUFFER, id);
					//int idx = (attrib.inputSlot > 0 ? m_flatIndeces[attrib.inputSlot - 1].size() : 0) + attrib.index;
					switch (attrib.format)
					{
					case FormatType::RGB32F:
						//glVertexAttribFormat(idx, 3, static_cast<GLenum>(DataType::FLOAT), false, attrib.offset);
						glVertexAttribPointer(attrib.index, 3, static_cast<GLenum>(DataType::FLOAT), false, attrib.stride, 0);
						break;
					case FormatType::RGBA32F:
						//glVertexAttribFormat(idx, 4, static_cast<GLenum>(DataType::FLOAT), false, attrib.offset);
						glVertexAttribPointer(attrib.index, 4, static_cast<GLenum>(DataType::FLOAT), false, attrib.stride, 0);
						break;
					case FormatType::R32U:
						//glVertexAttribFormat(idx, 1, static_cast<GLenum>(DataType::UINT), false, attrib.offset);
						glVertexAttribPointer(attrib.index, 1, static_cast<GLenum>(DataType::UINT), false, attrib.stride,0);
						break;
					case FormatType::RG32F:
						//glVertexAttribFormat(idx, 2, static_cast<GLenum>(DataType::FLOAT), false, attrib.offset);
						glVertexAttribPointer(attrib.index, 2, static_cast<GLenum>(DataType::FLOAT), false, attrib.stride, 0);
						break;
					default:
						log::warn("Format is not supported for vertex attributes");
						continue;
						break;
					}

					//glVertexAttribBinding(idx, attrib.inputSlot);
					glEnableVertexAttribArray(attrib.index);
					switch (attrib.inputClass)
					{
					case InputClass::PER_VERTEX:
						//glVertexBindingDivisor(idx, 0);
						glVertexAttribDivisor(attrib.index, 0);
						break;
					case InputClass::PER_INSTANCE:
						//glVertexBindingDivisor(idx, attrib.step);
						glVertexAttribDivisor(attrib.index, attrib.step);
						break;
					}
				}

				clearAttributes();
			}
		}

		void clearAttributes()
		{
			m_vertexAttribs.clear();
		}

		void release()
		{
			glDeleteVertexArrays(1, &id);
			clearAttributes();
		}
	};
}