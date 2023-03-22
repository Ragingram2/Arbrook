#pragma once
#include <string>
#include <D3D11.h>
#include <D3DX11.h>
#include <D3DX10.h>
#include <GLFW/glfw3.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

#include "core/math/math.hpp"

namespace rythe::rendering::internal
{
	struct window
	{
	private:
		static GLFWwindow* m_window;
	public:
		static IDXGISwapChain* swapchain;             // the pointer to the swap chain interface
		static ID3D11Device* dev;                     // the pointer to our Direct3D device interface
		static ID3D11DeviceContext* devcon;           // the pointer to our Direct3D device context
		static ID3D11RenderTargetView* backbuffer;    // global declaration
		math::ivec2 m_resolution;
		std::string m_windowName;

	public:
		window() = default;
		window(math::ivec2 res, const std::string& name) : m_resolution(res), m_windowName(name) { }

		GLFWwindow* getWindow()
		{
			return m_window;
		}

		void initialize(math::ivec2 res, const std::string& name)
		{
			m_window = glfwCreateWindow(res.x, res.y, name.c_str(), NULL, NULL);
		}

		void swapBuffers()
		{
			glfwSwapBuffers(m_window);
		}

		void setSwapInterval(int interval)
		{
			glfwSwapInterval(interval);
		}

		void pollEvents()
		{
			glfwPollEvents();
		}

		bool shouldClose()
		{
			return glfwWindowShouldClose(m_window);
		}

		static void makeCurrent()
		{
			glfwMakeContextCurrent(m_window);
		}
	};

	inline GLFWwindow* window::m_window;
	// global declarations
	inline IDXGISwapChain* window::swapchain;             // the pointer to the swap chain interface
	inline ID3D11Device* window::dev;                     // the pointer to our Direct3D device interface
	inline ID3D11DeviceContext* window::devcon;           // the pointer to our Direct3D device context
	inline ID3D11RenderTargetView* window::backbuffer;    // global declaration

}