#pragma once
#include <string>
#include <unordered_map>
#include <memory>

#include <GL/glew.h>

#include "core/core.hpp"
#include "rendering/data/definitions.hpp"
#include "rendering/data/texture.hpp"
#include "rendering/data/texturehandle.hpp"


namespace rythe::rendering
{
	class TextureCache
	{
	private:
		static RenderInterface m_api;
		static std::unordered_map<std::string, std::unique_ptr<texture>> m_textures;
	public:
		static texture_handle createTexture2D(const std::string& name, const std::string& filepath, texture_parameters params = { WrapMode::REPEAT, WrapMode::REPEAT, FilterMode::LINEAR_MIPMAP_LINEAR, FilterMode::LINEAR });
		static texture_handle getTexture2D(const std::string& name);
	};
}