#pragma once
#include "rendering/data/config.hpp"
#include EnumTypes_HPP_PATH
namespace rythe::rendering
{
	struct vertexattribute
	{
		const char* name;
		unsigned int index;
		internal::FormatType format;
		unsigned int stride;
		unsigned int offset;
	};
}