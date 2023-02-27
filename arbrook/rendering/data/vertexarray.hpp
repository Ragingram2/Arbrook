#pragma once
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <rythe/primitives>

#include "rendering/data/buffer.hpp"

namespace rythe::rendering
{
	enum UsageType
	{
		StaticDraw = GL_STATIC_DRAW,
	};

	struct vertexarray
	{
		GLuint m_id;
		buffer<index, unsigned int> m_indexBuffer;
		buffer<vertex, float> m_vertexBuffer;

		void initialize(int num = 1);
		void bind();
		void unbind();

		void bufferVertexData(float data[], int size, unsigned int usage);
		void bufferIndexData(unsigned int data[], int size, unsigned int usage);

		void setAttributePtr(int index, int components, GLenum type, bool normalize, int stride, const void* pointer = 0);
	};
}