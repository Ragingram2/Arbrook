#include "rendering/cache/texturecache.hpp"
#include <stb/stb_image.h>

namespace rythe::rendering
{
	std::unordered_map<std::string, std::unique_ptr<texture>> TextureCache::m_textures;

	texture_handle TextureCache::createTexture2D(RenderInterface& api, const std::string& name, const std::string& filepath, texture_parameters params)
	{
		if (m_textures.contains(name))
		{
			log::warn("Texture {} already exists, ignoring new texture, and returning existing one", name);
			return m_textures[name].get();
		}
		auto& tex = m_textures.emplace(name, std::make_unique<texture>()).first->second;

		return api.createTexture2D(tex.get(), name, filepath);
	}

	texture_handle TextureCache::getTexture2D(const std::string& name)
	{
		if (m_textures.contains(name))
		{
			return m_textures[name].get();
		}
		return nullptr;
	}
}