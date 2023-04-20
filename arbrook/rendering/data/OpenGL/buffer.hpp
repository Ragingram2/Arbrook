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
	template<typename APIType>
	struct Ibuffer;
}

namespace rythe::rendering::internal
{
	struct buffer
	{
		friend struct rendering::buffer_handle;
		friend struct Ibuffer<internal::buffer>;
	public:
		unsigned int id;
		std::string name;
		unsigned int bindId = 0;
	private:
		TargetType m_target;
		UsageType m_usage;
	public:

		template<typename elementType, typename dataType = elementType>
		void initialize(TargetType target, UsageType usage, int size)
		{
			m_target = target;
			m_usage = usage;

			glGenBuffers(1, &id);

			if (m_target == TargetType::CONSTANT_BUFFER)
			{
				glBindBuffer(static_cast<GLenum>(m_target), id);
				glBufferData(static_cast<GLenum>(m_target), size, nullptr, static_cast<GLenum>(m_usage));
				glBindBufferRange(static_cast<GLenum>(m_target), 0, id, 0, size);
			}
		}

		void bind()
		{
			glBindBuffer(static_cast<GLenum>(m_target), id);
		}

		template<typename elementType, typename dataType = elementType>
		void bufferData(elementType data[], int size)
		{
			glBindBuffer(static_cast<GLenum>(m_target), id);

			if (m_target == TargetType::CONSTANT_BUFFER)
			{
				glBufferSubData(static_cast<GLenum>(m_target), 0, size * sizeof(elementType), data);
			}
			else
			{
				glBufferData(static_cast<GLenum>(m_target), size * sizeof(elementType), data, static_cast<GLenum>(m_usage));
			}
		}
	};
}