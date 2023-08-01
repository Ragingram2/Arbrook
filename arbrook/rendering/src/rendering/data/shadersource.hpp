#pragma once
#include <string>
#include <sstream>

namespace rythe::rendering
{
	struct shader_source
	{
		std::string vertexSource;
		std::string fragSource;

		shader_source() = default;
		shader_source(std::stringstream ss[])
		{
			vertexSource = ss[0].str();
			fragSource = ss[1].str();
		}

	};

}