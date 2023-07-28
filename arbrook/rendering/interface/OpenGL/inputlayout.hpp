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
		std::vector<vertexattribute> m_vertexAttribs;
		std::unordered_map<int, std::set<int>> m_flatIndeces;
		std::vector<buffer_handle> m_buffers;
	public:

		void initialize(window& hwnd, unsigned int numBuffers, shader_handle shader)
		{
			m_hwnd = hwnd;
			glGenVertexArrays(1, &id);
		}

		//This needs to be reworked into having the buffers stored.
		void bind()
		{
			glBindVertexArray(id);

			if (m_vertexAttribs.size() > 0)
			{

				int bufId;
				glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &bufId);
				glBindVertexBuffer(m_vertexAttribs[0].inputSlot, bufId, 0, m_vertexAttribs[0].stride);
				for (auto& attrib : m_vertexAttribs)
				{
					int idx = (attrib.inputSlot > 0 ? m_flatIndeces[attrib.inputSlot-1].size(): 0) + attrib.index;
					switch (attrib.format)
					{
					case FormatType::RGB32F:
						glVertexAttribFormat(idx, 3, static_cast<GLenum>(DataType::FLOAT), false, attrib.offset);
						break;
					case FormatType::RGBA32F:
						glVertexAttribFormat(idx, 4, static_cast<GLenum>(DataType::FLOAT), false, attrib.offset);
						break;
					case FormatType::R32U:
						glVertexAttribFormat(idx, 1, static_cast<GLenum>(DataType::UINT), false, attrib.offset);
						break;
					case FormatType::RG32F:
						glVertexAttribFormat(idx, 2, static_cast<GLenum>(DataType::FLOAT), false, attrib.offset);
						break;
					default:
						log::warn("Format is not supported for vertex attributes");
						break;
					}

					glVertexAttribBinding(idx, attrib.inputSlot);
					glEnableVertexAttribArray(idx);
					switch (attrib.inputClass)
					{
					case InputClass::PER_VERTEX:
						glVertexBindingDivisor(idx, 0);
						break;
					case InputClass::PER_INSTANCE:
						glVertexBindingDivisor(idx, attrib.step);
						break;
					}
				}

				clearAttributes();
			}
		}

		void setAttributePtr(const std::string& attribName, unsigned int index, FormatType components, unsigned int inputSlot, unsigned int stride, unsigned int offset, InputClass inputClass, unsigned int instancedStep)
		{
			m_vertexAttribs.emplace_back(vertexattribute{ attribName.c_str(), index, components, inputSlot,stride, offset, inputClass, instancedStep });
			m_flatIndeces[inputSlot].insert(index);
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