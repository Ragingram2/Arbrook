#pragma once
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "core/core.hpp"

namespace rythe::rendering
{
	namespace math = core::math;
	struct texture
	{
		bool m_initialized = false;
		unsigned int m_id;
		int m_channels;

		int m_wrapModeS;
		int m_wrapModeT;
		int m_minFilterMode;
		int m_magFilterMode;
		math::ivec2 m_resolution;
		unsigned char* m_data;

		texture()
		{
			initialize();
		}

		void initialize();
		void bind();
		void unbind();

		void loadTexture(const std::string& filepath, int wrapModeS = GL_REPEAT, int wrapModeT = GL_REPEAT, int minFilterMode = GL_LINEAR_MIPMAP_LINEAR, int magFilterMode = GL_LINEAR);
	};
}