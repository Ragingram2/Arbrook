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

	void texture::loadTexture(const std::string& filepath, int wrapModeS, int wrapModeT, int minFilterMode, int magFilterMode)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapModeS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapModeT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilterMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilterMode);

		m_data = stbi_load(filepath.c_str(), &m_resolution.x, &m_resolution.y, &m_channels, 0);
		if (!m_data)
		{
			log::error("Image failed to load");
			return;
		}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_resolution.x, m_resolution.y, 0, GL_RGB, GL_UNSIGNED_BYTE, m_data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

}