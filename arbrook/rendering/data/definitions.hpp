#pragma once
#include "rendering/data/interface/irenderinterface.hpp"
#include "rendering/data/interface/ivertexarray.hpp"
#include "rendering/data/interface/ishader.hpp"
#include "rendering/data/interface/ibuffer.hpp"
#include "rendering/data/config.hpp"

namespace rythe::rendering
{
	typedef IRenderInterface<internal::RenderInterface> RenderInterface;
	typedef Ivertexarray<internal::vertexarray> vertexarray;
	typedef Ibuffer<internal::buffer<index, int>, index, int> indexBuffer;
	typedef Ibuffer<internal::buffer<vertex, float>, vertex, float> vertexBuffer;
	template<typename T, typename dataType>
	using buffer = Ibuffer<internal::buffer<T, dataType>, T, dataType>;
	typedef Ishader<internal::shader> shader;

	//make all of these enum classes and seperate
	enum UsageType
	{
		StaticDraw = RenderingAPI ? 0 : GL_STATIC_DRAW
	};

	//PrimitiveType
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
