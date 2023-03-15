#pragma once

namespace rythe::rendering::internal
{
	enum class UsageType
	{
		StaticDraw = 0
	};

	enum class PrimitiveType
	{
		TRIANGLES = 0
	};

	enum class DataType
	{
		INT = 0,
		UINT = 0,
		BYTE = 0,
		UBYTE = 0,
		SHORT = 0,
		USHORT = 0,
		FLOAT = 0
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