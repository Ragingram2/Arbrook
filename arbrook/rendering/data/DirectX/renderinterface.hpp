#pragma once
#include <string>
#include <d3d11.h>
//#include <d3dx11.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

// include the Direct3D Library file
#pragma comment (lib, "d3d11.lib")
//#pragma comment (lib, "d3dx11.lib")
//#pragma comment (lib, "d3dx10.lib")

#include "rendering/data/interface/window.hpp"

namespace rythe::rendering::internal
{
	class RenderInterface
	{
	public:
		void initialize(window& hwnd, math::ivec2 res, const std::string& name)
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			hwnd.initialize(res, name);
		}

		void close()
		{

		}
	};
}