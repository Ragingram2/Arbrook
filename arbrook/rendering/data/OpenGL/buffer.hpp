#pragma once
#include <vector>
#include <concepts>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <rythe/primitives>

#include "core/core.hpp"

namespace rythe::rendering::internal
{
	namespace math = core::math;

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

#include "rendering/data/OpenGL/buffer.inl"