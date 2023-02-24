#include "rendering/data/texture.hpp"
#include <stb/stb_image.h>

namespace rythe::rendering
{
	void texture::initialize()
	{
		glGenTextures(1, &m_id);
		bind();
		m_initialized = true;
	}

	void texture::bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_id);
	}

	void texture::unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void texture::loadTexture(const std::string& filepath, int wrapModeS, int wrapModeT, int minFilterMode, int magFilterMode)
	{
		if (!m_initialized)
			initialize();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapModeS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapModeT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilterMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilterMode);

		stbi_set_flip_vertically_on_load(true);
		m_data = stbi_load(filepath.c_str(), &m_resolution.x, &m_resolution.y, &m_channels, 0);
		if (!m_data)
		{
			log::error("Image failed to load");
			return;
		}

		switch (m_channels)
		{
		case 4:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_resolution.x, m_resolution.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);
			break;
		case 3:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_resolution.x, m_resolution.y, 0, GL_RGB, GL_UNSIGNED_BYTE, m_data);
			break;
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}

}