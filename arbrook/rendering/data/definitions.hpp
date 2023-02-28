#pragma once
#include "rendering/data/interface/irenderinterface.hpp"
#include "rendering/data/interface/ishader.hpp"
#include "rendering/data/config.hpp"

namespace rythe::rendering
{
	typedef IRenderInterface<internal::RenderInterface> RenderInterface;
	typedef Ishader<internal::shader> shader;
	//add definitions for a IShader, ITexture, etc
}
