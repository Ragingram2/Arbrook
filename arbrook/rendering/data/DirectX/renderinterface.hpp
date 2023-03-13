#pragma once
#include <string>
#include <d3d11.h>
#include <d3dx11.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

// include the Direct3D Library file
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

#include "core/math/math.hpp"
#include "core/logging/logging.hpp"
#include "rendering/data/shadersource.hpp"
#include "rendering/data/DirectX/shader.hpp"

#include "rendering/data/texturehandle.hpp"
#include "rendering/data/interface/window.hpp"

namespace rythe::rendering::internal
{
	class RenderInterface
	{
	private:
		// global declarations
		IDXGISwapChain* swapchain;             // the pointer to the swap chain interface
		ID3D11Device* dev;                     // the pointer to our Direct3D device interface
		ID3D11DeviceContext* devcon;           // the pointer to our Direct3D device context
		ID3D11RenderTargetView* backbuffer;    // global declaration
	public:
		void initialize(window& hwnd, math::ivec2 res, const std::string& name)
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			hwnd.initialize(res, name);

			// create a struct to hold information about the swap chain
			DXGI_SWAP_CHAIN_DESC scd;

			// clear out the struct for use
			ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

			// fill the swap chain description struct
			scd.BufferCount = 1;                                    // one back buffer
			scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
			scd.BufferDesc.Width = res.x;                    // set the back buffer width
			scd.BufferDesc.Height = res.y;                  // set the back buffer height
			scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
			scd.OutputWindow = glfwGetWin32Window(hwnd.getWindow());                                // the window to be used
			scd.SampleDesc.Count = 4;                               // how many multisamples
			scd.Windowed = TRUE;                                    // windowed/full-screen mode
			scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;     // allow full-screen switching

			// create a device, device context and swap chain using the information in the scd struct
			D3D11CreateDeviceAndSwapChain(NULL,
				D3D_DRIVER_TYPE_HARDWARE,
				NULL,
				NULL,
				NULL,
				NULL,
				D3D11_SDK_VERSION,
				&scd,
				&swapchain,
				&dev,
				NULL,
				&devcon);

			// get the address of the back buffer
			ID3D11Texture2D* pBackBuffer;
			swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

			// use the back buffer address to create the render target
			dev->CreateRenderTargetView(pBackBuffer, NULL, &backbuffer);
			pBackBuffer->Release();

			// set the render target as the back buffer
			devcon->OMSetRenderTargets(1, &backbuffer, NULL);

			// Set the viewport
			D3D11_VIEWPORT viewport;
			ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

			viewport.TopLeftX = 0;
			viewport.TopLeftY = 0;
			viewport.Width = res.x;
			viewport.Height = res.y;

			devcon->RSSetViewports(1, &viewport);
		}

		void close()
		{
			swapchain->SetFullscreenState(FALSE, NULL);    // switch to windowed mode

			// close and release all existing COM objects
			swapchain->Release();
			backbuffer->Release();
			dev->Release();
			devcon->Release();
		}

		void swapBuffers(window& hwnd)
		{
			swapchain->Present(0, 0);
		}

		void drawArrays(unsigned int mode, int first, int count)
		{

		}

		void drawArraysInstanced(unsigned int mode, int first, int count, int instanceCount)
		{

		}

		void drawIndexed(unsigned int mode, int count, unsigned int type, const void* indecies)
		{

		}

		void drawIndexdInstanced(unsigned int mode, int count, unsigned int type, const void* indecies, int instanceCount)
		{

		}

		void bind(shader* shader)
		{

		}

		void bind(texture_handle handle)
		{

		}

		void unbind(shader* shader)
		{

		}

		void unbind(texture_handle handle)
		{
		}

		void clear(int flags)
		{

		}

		void setClearColor(math::vec4 color)
		{
			float colorData[] = { color.r, color.g, color.b, color.a };
			devcon->ClearRenderTargetView(backbuffer, colorData);
		}

		void enableStencil()
		{

		}

		void disableStencil()
		{

		}

		void setClearStencil()
		{

		}

		void setStencilOp(unsigned int fail, unsigned int zfail, unsigned int zpass)
		{

		}

		void setStencilFunc(unsigned int func, int ref, unsigned int mask)
		{

		}

		//createVAO();

		void createShader(shader* shader, const std::string& name, const std::string& filepath)
		{
			// load and compile the two shaders
			ID3D10Blob* VS, * PS;
			D3DX11CompileFromFile(L"shaders.shader", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
			D3DX11CompileFromFile(L"shaders.shader", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);
		}

		texture_handle createTexture2D(texture* texture, const std::string& name, const std::string& filepath, texture_parameters params = { GL_REPEAT ,GL_REPEAT,GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR })
		{
			return texture;
		}
	};
}