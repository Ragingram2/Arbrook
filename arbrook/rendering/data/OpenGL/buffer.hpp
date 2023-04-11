#pragma once
#include <vector>
#include <concepts>

#include <GL/glew.h>

#include <rythe/primitives>

#include "core/core.hpp"

#include "rendering/data/config.hpp"
#include EnumTypes_HPP_PATH

namespace rythe::rendering
{
	struct buffer_handle;
}

namespace rythe::rendering::internal
{
	struct buffer
	{
		friend struct rendering::buffer_handle;
	public:
		unsigned int id;
	private:
		TargetType m_target;
		UsageType m_usage;
		int m_numBuffers = 1;
	public:

		void initialize(TargetType target, UsageType usage)
		{
			m_target = target;
			m_usage = usage;

			glGenBuffers(m_numBuffers, &id);

			bind();
		}

		void bind()
		{
			glBindBuffer(static_cast<GLenum>(m_target), id);
		}

		template<typename dataType>
		void bufferData(dataType data[], int size)
		{
			bind();
			glBufferData(static_cast<GLenum>(m_target), size, data, static_cast<GLenum>(m_usage));
		}

		//void setAttributePtr(int index, int components, DataType type, bool normalize, int stride, const void* pointer = 0)
		//{
		//	bind();

		//	glEnableVertexAttribArray(index);
		//	glVertexAttribPointer(index, components, static_cast<GLenum>(type), normalize, stride, pointer);
		//}
	};
}