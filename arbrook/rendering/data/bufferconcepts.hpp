#pragma once
#include <concepts>
namespace rythe::rendering
{
	struct buffer_element_type { };
	struct vertex : public buffer_element_type { };
	struct index : public buffer_element_type { };
	struct constant : public buffer_element_type { };

	template<typename T>
	concept validType = std::derived_from<T, buffer_element_type>;
}