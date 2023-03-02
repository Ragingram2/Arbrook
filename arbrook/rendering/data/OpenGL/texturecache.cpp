#include "rendering/data/OpenGL/texturecache.hpp"
#include <stb/stb_image.h>

namespace rythe::rendering::internal
{
	std::unordered_map<std::string, std::unique_ptr<texture>> TextureCache::m_textures;

	texture* TextureCache::createTexture2D(const std::string& name, const std::string& filepath, texture_parameters params)
	{
		if (m_textures.contains(name))
		{
			log::warn("Texture {} already exists, ignoring new texture, and returning existing one", name);
			return m_textures[name].get();
		}

		auto& tex = m_textures.emplace(name, std::make_unique<texture>()).first->second;
		tex->m_name = name;
		auto& resolution = tex->m_params.m_resolution;
		auto& channels = tex->m_params.m_channels;
		unsigned int& id = tex->m_id;
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, params.m_wrapModeS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, params.m_wrapModeT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, params.m_minFilterMode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, params.m_magFilterMode);
		stbi_set_flip_vertically_on_load(true);

		tex->m_data = stbi_load(filepath.c_str(), &resolution.x, &resolution.y, &channels, 0);
		if (!tex->m_data)
		{
			log::error("Image failed to load");
			return nullptr;
		}

		switch (channels)
		{
		case 4:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, resolution.x, resolution.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex->m_data);
			break;
		case 3:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, resolution.x, resolution.y, 0, GL_RGB, GL_UNSIGNED_BYTE, tex->m_data);
			break;
		}
		glGenerateMipmap(GL_TEXTURE_2D);

		return m_textures[name].get();
	}

	texture* TextureCache::getTexture2D(const std::string& name)
	{
		if (m_textures.contains(name))
		{
			auto tex = m_textures[name].get();
			glBindTexture(GL_TEXTURE_2D, *tex);
			return tex;
		}
		return nullptr;
	}
}