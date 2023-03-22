#pragma once
#include <vector>
#include <concepts>

#include <GL/glew.h>

#include <rythe/primitives>

#include "core/core.hpp"

#include "rendering/data/config.hpp"
#include EnumTypes_HPP_PATH

namespace rythe::rendering::internal
{
	struct buffer
	{
		unsigned int m_id;
	private:
		TargetType m_target;
		UsageType m_usage;
		int m_numBuffers = 1;

	public:

		void initialize(TargetType target, UsageType usage)
		{
			m_target = target;
			m_usage = usage;

			glGenBuffers(m_numBuffers, &m_id);

			glBindBuffer(static_cast<GLenum>(m_target), 0);
			glBindBuffer(static_cast<GLenum>(m_target), m_id);
		}

		template<typename dataType>
		void bufferData(dataType data[], int size)
		{
			glBindBuffer(static_cast<GLenum>(m_target), 0);
			glBindBuffer(static_cast<GLenum>(m_target), m_id);

			std::vector<dataType> m_data;
			m_data.insert(m_data.end(), &data[0], &data[size]);
			glBufferData(static_cast<GLenum>(m_target), size, m_data.data(), static_cast<GLenum>(m_usage));
		}

		void setAttributePtr(int index, int components, DataType type, bool normalize, int stride, const void* pointer = 0)
		{
			glBindBuffer(static_cast<GLenum>(m_target), 0);
			glBindBuffer(static_cast<GLenum>(m_target), m_id);

			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, components, static_cast<GLenum>(type), normalize, stride, pointer);
		}
	};
}