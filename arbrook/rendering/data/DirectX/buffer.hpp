#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>

#include "rendering/data/bufferconcepts.hpp"

namespace rythe::rendering::internal
{
	struct VERTEX
	{
		float X, Y, Z;      // position
		D3DXCOLOR Color;    // color
	};

	template<typename T, typename dataType>
		requires rendering::validType<T>
	struct buffer
	{

	};
}