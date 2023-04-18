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
	private:
		TargetType m_target;
		UsageType m_usage;
	public:

		void initialize(TargetType target, UsageType usage)
		{
			m_target = target;
			m_usage = usage;

			glGenBuffers(1, &id);
		}

		void bind()
		{
			glBindBuffer(static_cast<GLenum>(m_target), id);
		}

		template<typename elementType, typename dataType = elementType>
		void bufferData(elementType data[], int size)
		{
			glBindBuffer(static_cast<GLenum>(m_target), id);
			glBufferData(static_cast<GLenum>(m_target), size * sizeof(elementType), data, static_cast<GLenum>(m_usage));
		}
	};
}