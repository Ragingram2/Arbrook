#pragma once
#include "rendering/data/definitions.hpp"
#include "rendering/data/texturehandle.hpp"
#include "rendering/data/shaderhandle.hpp"
#include "rendering/data/mesh.hpp"
namespace rythe::rendering
{
	struct mesh_renderer
	{
		mesh mesh;

		texture_handle texture;
		shader_handle shader;
		inputlayout layout;
	};
}