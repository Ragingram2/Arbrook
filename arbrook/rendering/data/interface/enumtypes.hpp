#pragma once
#include "rendering/data/config.hpp"
#include EnumTypes_HPP_PATH

namespace rythe::rendering
{
	enum class TargetType
	{
		ARRAY_BUFFER = static_cast<int>(internal::TargetType::ARRAY_BUFFER),
		ELEMENT_ARRAY_BUFFER = static_cast<int>(internal::TargetType::ELEMENT_ARRAY_BUFFER),
		TEXTURE2D = static_cast<int>(internal::TargetType::TEXTURE2D)
	};

	enum class UsageType
	{
		StaticDraw = static_cast<int>(internal::UsageType::StaticDraw)
	};

	enum class PrimitiveType
	{
		TRIANGLES = static_cast<int>(internal::PrimitiveType::TRIANGLES),
		TRIANGLESLIST = static_cast<int>(internal::PrimitiveType::TRIANGLESLIST)
	};

	enum class DataType
	{
		INT = static_cast<int>(internal::DataType::INT),
		UINT = static_cast<int>(internal::DataType::UINT),
		BYTE = static_cast<int>(internal::DataType::BYTE),
		UBYTE = static_cast<int>(internal::DataType::UBYTE),
		SHORT = static_cast<int>(internal::DataType::SHORT),
		USHORT = static_cast<int>(internal::DataType::USHORT),
		FLOAT = static_cast<int>(internal::DataType::FLOAT)
	};

	enum class WrapMode
	{
		CLAMP = static_cast<int>(internal::WrapMode::CLAMP),
		CLAMP_TO_EDGE = static_cast<int>(internal::WrapMode::CLAMP_TO_EDGE),
		CLAMP_TO_BORDER = static_cast<int>(internal::WrapMode::CLAMP_TO_BORDER),
		REPEAT = static_cast<int>(internal::WrapMode::REPEAT)
	};

	enum class FilterMode
	{
		NEAREST = static_cast<int>(internal::FilterMode::NEAREST),
		LINEAR = static_cast<int>(internal::FilterMode::LINEAR),
		NEAREST_MIPMAP_NEAREST = static_cast<int>(internal::FilterMode::NEAREST_MIPMAP_NEAREST),
		NEAREST_MIPMAP_LINEAR = static_cast<int>(internal::FilterMode::NEAREST_MIPMAP_LINEAR),
		LINEAR_MIPMAP_NEAREST = static_cast<int>(internal::FilterMode::LINEAR_MIPMAP_NEAREST),
		LINEAR_MIPMAP_LINEAR = static_cast<int>(internal::FilterMode::LINEAR_MIPMAP_LINEAR)
	};
}