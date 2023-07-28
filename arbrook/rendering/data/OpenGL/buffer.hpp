#pragma once
#include <vector>
#include <concepts>

#include <GL/glew.h>

#include <rsl/primitives>

#include "core/core.hpp"

#include "rendering/data/config.hpp"
#include EnumTypes_HPP_PATH

namespace rythe::rendering
{
	struct buffer_handle;
	template<typename APIType>
	struct Ibuffer;

	namespace internal
	{
		struct inputlayout;
	}
}

namespace rythe::rendering::internal
{
	struct buffer
	{
		friend struct rendering::buffer_handle;
		friend struct Ibuffer<internal::buffer>;
		friend struct internal::inputlayout;
	public:
		unsigned int id;
		std::string name;
		unsigned int bindId = 0;
	private:
		TargetType m_target;
		UsageType m_usage;
		unsigned int m_slot;
		unsigned int m_offset;
		unsigned int m_size;
		unsigned int m_elementSize;
	public:

		template<typename elementType>
		void initialize(TargetType target, UsageType usage, int size)
		{
			m_target = target;
			m_usage = usage;
			m_size = size;
			m_elementSize = sizeof(elementType);

			createBuffer();
		}

		void bind(int slot = 0, int offset = 0)
		{
			glBindBuffer(static_cast<GLenum>(m_target), id);
			m_slot = slot;
			m_offset = offset;
		}

		template<typename elementType>
		void bufferData(elementType data[], int size = 1)
		{
			bind();

			if (size < 1)
			{
				size = m_size;
			}
			else if (size != m_size)
			{
				m_size = size;
				m_elementSize = sizeof(elementType);
				createBuffer();
			}

			if (m_target == TargetType::CONSTANT_BUFFER)
			{
				glBufferSubData(static_cast<GLenum>(m_target), 0, m_size * sizeof(elementType), data);
			}
			else
			{
				glBufferData(static_cast<GLenum>(m_target), m_size * sizeof(elementType), data, static_cast<GLenum>(m_usage));
			}
		}

	private:
		void createBuffer()
		{
			if (id == 0)
				glGenBuffers(1, &id);

			bind();
			glBufferData(static_cast<GLenum>(m_target), m_size * m_elementSize, nullptr, static_cast<GLenum>(m_usage));
			if (m_target == TargetType::CONSTANT_BUFFER)
			{
				glBindBufferRange(static_cast<GLenum>(m_target), 0, id, 0, m_elementSize);
			}
		}
	};
}