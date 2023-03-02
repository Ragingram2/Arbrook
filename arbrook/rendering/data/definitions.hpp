#pragma once
#include "rendering/data/interface/irenderinterface.hpp"
#include "rendering/data/interface/ivertexarray.hpp"
#include "rendering/data/config.hpp"

namespace rythe::rendering
{
	typedef IRenderInterface<internal::RenderInterface> RenderInterface;
	typedef Ivertexarray<internal::vertexarray> vertexarray;
}
