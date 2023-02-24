#include "rendering/data/texture.hpp"

namespace rythe::rendering
{
	void texture::initialize()
	{
		glGenTextures(1, &m_id);
		bind();
	}

	void texture::bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	void texture::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void texture::writeTexture(math::ivec2 resolution, unsigned int internalFormat, unsigned int format, unsigned int compType, unsigned char* data)
	{
		m_resolution = resolution;
		m_data = data;

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, resolution.x, resolution.y, 0, format, compType, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	void texture::setParameter(unsigned int param, unsigned int mode)
	{
		glTexParameteri(GL_TEXTURE_2D, param, mode);
	}
}