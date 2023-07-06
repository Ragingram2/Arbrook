#pragma once
#include "rendering/data/definitions.hpp"
#include "rendering/data/texturehandle.hpp"
#include "rendering/data/shaderhandle.hpp"
#include "rendering/data/vertex.hpp"

namespace rythe::rendering
{
	struct sprite_renderer
	{
		//vertex verticies[4] =
		//{	//positions						//colors								//tex coors
		//	{ { -0.1f, 0.1f, 0.0f },			{ 1.0f, 0.0f, 0.0f, 1.0f },		{ 0.0f, 1.0f } },//0
		//	{ {	-0.1f,-0.1f, 0.0f },			{ 0.0f, 1.0f, 0.0f, 1.0f },		{ 0.0f, 0.0f } },//1
		//	{ { 0.1f,-0.1f, 0.0f },			{ 0.0f, 0.0f, 1.0f, 1.0f },		{ 1.0f, 0.0f } },//2
		//	{ { 0.1f, 0.1f, 0.0f },			{ 1.0f, 1.0f, 0.0f, 1.0f },		{ 1.0f, 1.0f } }//3
		//};
		//unsigned int indicies[4] =
		//{
		//	1,2,0,3
		//};

		texture_handle texture;
		shader_handle shader;
		inputlayout layout;

		sprite_renderer() = default;
		sprite_renderer(texture_handle t_handle, shader_handle s_handle) : texture(t_handle), shader(s_handle) {}

	};
}