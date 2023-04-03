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
		TRIANGLESLIST = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		TRIANGLESTRIP = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
		LINELIST = D3D11_PRIMITIVE_TOPOLOGY_LINELIST,
		LINESTRIP = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP,
		POINTLIST = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST
	};

	enum class DataType
	{
		INT = sizeof(int),
		UINT = sizeof(unsigned int),
		BYTE = sizeof(char),
		UBYTE = sizeof(unsigned char),
		SHORT = sizeof(short int),
		USHORT = sizeof(unsigned short int),
		FLOAT = sizeof(float)
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