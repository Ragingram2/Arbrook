#include "rendering/cache/texturecache.hpp"
#include <stb/stb_image.h>

namespace rythe::rendering
{
	std::unordered_map<std::string, std::unique_ptr<texture>> TextureCache::m_textures;

	texture_handle TextureCache::createTexture2D(const std::string& name, const std::string& filepath, texture_parameters params, bool generateMipMaps)
	{
		if (m_textures.contains(name))
		{
			log::warn("Texture {} already exists, ignoring new texture, and returning existing one", name);
			return m_textures[name].get();
		}
		auto tex = m_textures.emplace(name, std::make_unique<texture>()).first->second.get();
		tex->m_impl.name = name;
		tex->m_impl.initialize(internal::TargetType::TEXTURE2D, params, generateMipMaps);
		tex->loadData(filepath);

		return { tex };
	}

	texture_handle TextureCache::getTexture2D(const std::string& name)
	{
		if (m_textures.contains(name))
		{
			return m_textures[name].get();
		}
		return texture_handle{ nullptr };
	}
}