#pragma once
#include <string>
#include <unordered_map>
#include <memory>

#include <GL/glew.h>

#include "core/core.hpp"
#include "rendering/data/interface/texture.hpp"

namespace rythe::rendering::internal
{
	class TextureCache
	{
	private:
		static std::unordered_map<std::string, std::unique_ptr<texture>> m_textures;
	public:
		static texture* createTexture2D(const std::string& name, const std::string& filepath, texture_parameters params = { GL_REPEAT ,GL_REPEAT,GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR });
		static texture* getTexture2D(const std::string& name);
	};
}