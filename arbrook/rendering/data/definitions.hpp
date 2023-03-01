#pragma once
#include "rendering/data/interface/shader.hpp"
#include "rendering/data/interface/irenderinterface.hpp"
#include "rendering/data/interface/ishadercache.hpp"
#include "rendering/data/interface/itexture.hpp"
#include "rendering/data/interface/ivertexarray.hpp"
#include "rendering/data/config.hpp"

namespace rythe::rendering
{
	typedef IRenderInterface<internal::RenderInterface> RenderInterface;
	typedef IShaderCache<internal::ShaderCache> ShaderCache;
	//typedef Ishader<internal::shader> shader;
	typedef Itexture<internal::texture> texture;
	typedef Ivertexarray<internal::vertexarray> vertexarray;
	//add definitions for a IShader, ITexture, etc
}
