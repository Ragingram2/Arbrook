#pragma once
#include <vector>
#include <concepts>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <rythe/primitives>

#include "core/math/math.hpp"

namespace rythe::rendering
{
	namespace math = core::math;

	//enum BUFFER_TYPES
	//{
	//	VERTEX = GL_ARRAY_BUFFER,
	//	INDEX = GL_ELEMENT_ARRAY_BUFFER,
	//	CONSTANT = 1
	//};

	struct buffer_element_type { };
	struct vertex : public buffer_element_type { };
	struct index : public buffer_element_type { };
	struct constant : public buffer_element_type { };

	template<typename T>
	concept validType = std::derived_from<T, buffer_element_type>;

	template<typename T, typename dataType>
		requires validType<T>
	struct buffer
	{
		unsigned int m_id;
		GLenum m_type;//enum
		GLenum m_usage;//enum
		int m_numBuffers = 1;
		std::vector<dataType> m_data;

		buffer(int n = 1) : m_numBuffers(n) { /*initialize(n);*/ }

		void initialize();
		void bind();
		void unbind();

		void bufferData(dataType data[], int size, unsigned int usage);
		void setAttributePtr(int index, int components, unsigned int type, bool normalize, int stride, const void* pointer = 0);
	};

}

#include "rendering/data/buffer.inl"