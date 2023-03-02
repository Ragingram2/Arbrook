#pragma once
#include "rendering/data/interface/irenderinterface.hpp"
#include "rendering/data/interface/ishadercache.hpp"
#include "rendering/data/interface/itexturecache.hpp"
#include "rendering/data/interface/ivertexarray.hpp"
#include "rendering/data/config.hpp"

namespace rythe::rendering
{
	typedef IRenderInterface<internal::RenderInterface> RenderInterface;
	typedef IShaderCache<internal::ShaderCache> ShaderCache;
	typedef ITextureCache<internal::TextureCache> TextureCache;
	typedef Ivertexarray<internal::vertexarray> vertexarray;
	//add definitions for a IShader, ITexture, etc
}
