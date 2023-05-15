#pragma once
#include <functional>

#include "rendering/data/definitions.hpp"
#include "rendering/data/vertex.hpp"


namespace rythe::rendering
{
	struct testrenderer
	{
		unsigned int testId = 0;
		inputlayout layout;

		std::function<void> test;

		testrenderer() = default;
		testrenderer(unsigned int id, inputlayout input) : testId(id), layout(input) {}
	};
}