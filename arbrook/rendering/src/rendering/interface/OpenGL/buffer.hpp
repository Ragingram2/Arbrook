#pragma once
#include <vector>
#include <concepts>


#include <rsl/primitives>

#include "rendering/interface/OpenGL/oglincludes.hpp"
#include "rendering/interface/config.hpp"
#include EnumTypes_HPP_PATH

namespace rythe::rendering
{
	template<typename APIType>
	struct Ibuffer;
	namespace internal
	{
		struct buffer;
	}
}

namespace rythe::rendering::internal
{
	struct buffer
	{
		friend struct Ibuffer<internal::buffer>;
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

			if (m_target == TargetType::CONSTANT_BUFFER || m_usage == UsageType::IMMUTABLE)
			{
				glBufferSubData(static_cast<GLenum>(m_target), 0, m_size * sizeof(elementType), data);
			}
			else
			{
				glBufferData(static_cast<GLenum>(m_target), m_size * sizeof(elementType), data, static_cast<GLenum>(m_usage));
			}
		}

		void release()
		{
			glDeleteBuffers(1, &id);
		}

	private:
		void createBuffer()
		{
			if (id == 0)
				glGenBuffers(1, &id);

			bind();
			if (m_usage == UsageType::IMMUTABLE)
			{
				glBufferStorage(static_cast<GLenum>(m_target), m_size * m_elementSize, 0, GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT);
			}
			else
			{
				glBufferData(static_cast<GLenum>(m_target), m_size * m_elementSize, nullptr, static_cast<GLenum>(m_usage));
				if (m_target == TargetType::CONSTANT_BUFFER)
				{
					glBindBufferRange(static_cast<GLenum>(m_target), 0, id, 0, m_elementSize);
				}
			}
		}
	};
}