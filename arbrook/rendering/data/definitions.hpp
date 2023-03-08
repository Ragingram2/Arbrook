#pragma once
#include "rendering/data/interface/irenderinterface.hpp"
#include "rendering/data/interface/ivertexarray.hpp"
#include "rendering/data/interface/iwindow.hpp"
#include "rendering/data/config.hpp"

namespace rythe::rendering
{
	typedef IRenderInterface<internal::RenderInterface> RenderInterface;
	typedef Ivertexarray<internal::vertexarray> vertexarray;
	typedef Iwindow<internal::window> window;

	enum DrawMode
	{
		TRIANGLES = RenderingAPI ? 0 : GL_TRIANGLES
	};

	enum DataType
	{
		INT = RenderingAPI ? 0 : GL_INT,
		UINT = RenderingAPI ? 0 : GL_UNSIGNED_INT,
		BYTE = RenderingAPI ? 0 : GL_BYTE,
		UBYTE = RenderingAPI ? 0 : GL_UNSIGNED_BYTE,
		SHORT = RenderingAPI ? 0 : GL_SHORT,
		USHORT = RenderingAPI ? 0 : GL_UNSIGNED_SHORT,
		FLOAT = RenderingAPI ? 0 : GL_FLOAT
	};
}
