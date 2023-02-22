#pragma once
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <rythe/primitives>

#include "rendering/data/buffer.hpp"

namespace rythe::rendering
{
	struct vertexarray
	{
		GLuint m_id;
		buffer<index, unsigned int> m_indexBuffer;
		buffer<vertex, float> m_vertexBuffer;

		void initialize();
		void bind();
		void unbind();
	};
}