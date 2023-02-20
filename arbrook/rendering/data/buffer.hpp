#pragma once
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace rythe::rendering
{
	template<typename T>
	struct buffer
	{
		unsigned int m_id;
		GLenum m_type;
		GLenum m_usage;
		GLsizei m_num = 1;
		std::vector<T> m_data;

		buffer() = default;
		buffer(GLenum type, GLsizei n = 1) : m_type(type), m_num(n) { initialize(type, n); }

		void initialize(GLenum type, GLsizei n = 1);
		void bind();
		void unbind();
		void bufferData(T data[], int size, GLenum usage);
		void setAttributePtr(int index, int components, GLenum type, bool normalize, const void* pointer = 0);
	};
}

#include "rendering/data/buffer.inl"