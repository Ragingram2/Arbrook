#pragma once
#include <vector>
#include <concepts>

#include <GL/glew.h>

#include <rythe/primitives>

#include "core/core.hpp"
#include "rendering/data/bufferconcepts.hpp"

#include "rendering/data/config.hpp"
#include EnumTypes_HPP_PATH

namespace rythe::rendering::internal
{
	template<typename T, typename dataType>
		requires rendering::validType<T>
	struct buffer
	{
		unsigned int m_id;
		TargetType m_target;//enum
		UsageType m_usage;//enum
		int m_numBuffers = 1;
		std::vector<dataType> m_data;

		buffer(int n = 1) : m_numBuffers(n) { /*initialize(n);*/ }

		void initialize();
		void bind();
		void unbind();

		void bufferData(dataType data[], int size, UsageType usage);
		void setAttributePtr(int index, int components, DataType type, bool normalize, int stride, const void* pointer = 0);
	};

	template<>
	inline void buffer<vertex, float>::initialize()
	{
		m_target = TargetType::ARRAY_BUFFER;
		glGenBuffers(m_numBuffers, &m_id);
		bind();
	}

	template<>
	inline void buffer<index, unsigned int>::initialize()
	{
		m_target = TargetType::ELEMENT_ARRAY_BUFFER;
		glGenBuffers(m_numBuffers, &m_id);
		bind();
	}


	template<typename T, typename dataType>
		requires validType<T>
	inline void buffer<T, dataType>::bind()
	{
		glBindBuffer(static_cast<GLenum>(m_target), m_id);
	}

	template<typename T, typename dataType>
		requires validType<T>
	inline void buffer<T, dataType>::unbind()
	{
		glBindBuffer(static_cast<GLenum>(m_target), 0);
	}

	template<typename T, typename dataType>
		requires validType<T>
	inline void buffer<T, dataType>::bufferData(dataType data[], int size, UsageType usage)
	{
		m_data.insert(m_data.end(), &data[0], &data[size]);
		m_usage = usage;
		glBufferData(static_cast<GLenum>(m_target), size, m_data.data(), static_cast<GLenum>(usage));
	}

	template<typename T, typename dataType>
		requires validType<T>
	inline void buffer<T, dataType>::setAttributePtr(int index, int components, DataType type, bool normalize, int stride, const void* pointer)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, components, static_cast<GLenum>(type), normalize, stride, pointer);
	}
}