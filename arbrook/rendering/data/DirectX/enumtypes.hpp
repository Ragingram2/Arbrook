#pragma once
#include <D3D11.h>
#include <D3Dcommon.h>

namespace rythe::rendering::internal
{
	enum class TargetType
	{
		ARRAY_BUFFER = D3D11_BIND_VERTEX_BUFFER,
		ELEMENT_ARRAY_BUFFER = D3D11_BIND_INDEX_BUFFER,
		TEXTURE2D = 0
	};

	enum class UsageType
	{
		StaticDraw = D3D11_USAGE_DYNAMIC
	};

	enum class PrimitiveType
	{
		TRIANGLES = D3D10_PRIMITIVE_TRIANGLE,
		TRIANGLESLIST = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST
	};

	enum class DataType
	{
		INT = D3D_SVT_INT,
		UINT = D3D_SVT_UINT,
		BYTE = 0,
		UBYTE = 0,
		SHORT = D3D_SVT_INT,
		USHORT = D3D_SVT_UINT8,
		FLOAT = D3D_SVT_FLOAT
	};

	enum class WrapMode
	{
		CLAMP = 0,
		CLAMP_TO_EDGE = 0,
		CLAMP_TO_BORDER = 0,
		REPEAT = 0
	};

	enum class FilterMode
	{
		NEAREST = 0,
		LINEAR = 0,
		NEAREST_MIPMAP_NEAREST = 0,
		NEAREST_MIPMAP_LINEAR = 0,
		LINEAR_MIPMAP_NEAREST = 0,
		LINEAR_MIPMAP_LINEAR = 0
	};
}