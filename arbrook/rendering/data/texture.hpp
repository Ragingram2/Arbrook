#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "core/core.hpp"

namespace rythe::rendering
{
	namespace math = core::math;
	struct texture
	{
		unsigned int m_id;
		math::ivec2 m_resolution;
		unsigned char* m_data;

		void initialize();
		void bind();
		void unbind();

		void writeTexture(math::ivec2 resolution, unsigned int internalFormat, unsigned int format, unsigned int compType, unsigned char* data);

		void setParameter(unsigned int param, unsigned int mode);
	};
}