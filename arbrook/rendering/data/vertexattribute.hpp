#pragma once
#include <memory>
#include <string>

#include "rendering/data/config.hpp"
#include EnumTypes_HPP_PATH
namespace rythe::rendering
{
	struct vertexattribute
	{
	public:
		std::string name;
		unsigned int index;
		internal::FormatType format;
		unsigned int stride;
		unsigned int offset;
		internal::InputClass inputClass;

	public:
		vertexattribute() = default;
		vertexattribute(const std::string&& nam, unsigned int idx, internal::FormatType frmt, unsigned int strd, unsigned int offst,internal::InputClass inputClass) : name(nam), index(idx), format(frmt), stride(strd), offset(offst), inputClass(inputClass) {}
	};
}