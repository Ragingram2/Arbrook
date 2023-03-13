#pragma once
#include "rendering/data/bufferconcepts.hpp"

namespace rythe::rendering::internal
{
	template<typename T, typename dataType>
		requires rendering::validType<T>
	struct buffer
	{

	};
}