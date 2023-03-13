#pragma once
#include <vector>
#include <concepts>

#include <GL/glew.h>

#include <rythe/primitives>

#include "core/core.hpp"
#include "rendering/data/bufferconcepts.hpp"

namespace rythe::rendering::internal
{
	template<typename T, typename dataType>
		requires rendering::validType<T>
	struct buffer
	{
		unsigned int m_id;
		unsigned int m_type;//enum
		unsigned int m_usage;//enum
		int m_numBuffers = 1;
		std::vector<dataType> m_data;

		buffer(int n = 1) : m_numBuffers(n) { /*initialize(n);*/ }

		void initialize();
		void bind();
		void unbind();

		void bufferData(dataType data[], int size, unsigned int usage);
		void setAttributePtr(int index, int components, unsigned int type, bool normalize, int stride, const void* pointer = 0);
	};

	template<>
	inline void buffer<vertex, float>::initialize()
	{
		m_type = GL_ARRAY_BUFFER;
		glGenBuffers(m_numBuffers, &m_id);
		bind();
	}

	template<>
	inline void buffer<index, unsigned int>::initialize()
	{
		m_type = GL_ELEMENT_ARRAY_BUFFER;
		glGenBuffers(m_numBuffers, &m_id);
		bind();
	}


	template<typename T, typename dataType>
		requires validType<T>
	inline void buffer<T, dataType>::bind()
	{
		glBindBuffer(m_type, m_id);
	}

	template<typename T, typename dataType>
		requires validType<T>
	inline void buffer<T, dataType>::unbind()
	{
		glBindBuffer(m_type, 0);
	}

	template<typename T, typename dataType>
		requires validType<T>
	inline void buffer<T, dataType>::bufferData(dataType data[], int size, GLenum usage)
	{
		m_data.insert(m_data.end(), &data[0], &data[size]);
		m_usage = usage;
		glBufferData(m_type, size, m_data.data(), usage);
	}

	template<typename T, typename dataType>
		requires validType<T>
	inline void buffer<T, dataType>::setAttributePtr(int index, int components, GLenum type, bool normalize, int stride, const void* pointer)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, components, type, normalize, stride, pointer);
	}
}