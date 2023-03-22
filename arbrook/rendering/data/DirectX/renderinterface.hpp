#pragma once
#include <string>
#include <fstream>
#include <D3D11.h>
#include <D3DX11.h>
#include <D3DX10.h>
#include <D3Dcompiler.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")
#pragma comment(lib, "D3DCompiler.lib")

#include "core/math/math.hpp"
#include "core/logging/logging.hpp"
#include "rendering/data/shadersource.hpp"
#include "rendering/data/texturehandle.hpp"
#include "rendering/data/config.hpp"

#include Window_HPP_PATH
#include Shader_HPP_PATH
#include Buffer_HPP_PATH

namespace rythe::rendering::internal
{
	class RenderInterface
	{
	public:
		void initialize(window& hwnd, math::ivec2 res, const std::string& name)
		{
			log::debug("Initializing DX11");
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			hwnd.initialize(res, name);

			DXGI_SWAP_CHAIN_DESC scd;

			ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

			scd.BufferCount = 1;                                    // one back buffer
			scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
			scd.BufferDesc.Width = res.x;                    // set the back buffer width
			scd.BufferDesc.Height = res.y;                  // set the back buffer height
			scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
			scd.OutputWindow = glfwGetWin32Window(hwnd.getWindow());                                // the window to be used
			scd.SampleDesc.Count = 4;                               // how many multisamples
			scd.Windowed = TRUE;                                    // windowed/full-screen mode
			scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;     // allow full-screen switching

			D3D11CreateDeviceAndSwapChain(NULL,
				D3D_DRIVER_TYPE_HARDWARE,
				NULL,
				NULL,
				NULL,
				NULL,
				D3D11_SDK_VERSION,
				&scd,
				&window::swapchain,
				&window::dev,
				NULL,
				&window::devcon);

			ID3D11Texture2D* pBackBuffer;
			window::swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

			window::dev->CreateRenderTargetView(pBackBuffer, NULL, &window::backbuffer);
			pBackBuffer->Release();

			window::devcon->OMSetRenderTargets(1, &window::backbuffer, NULL);

			D3D11_VIEWPORT viewport;
			ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

			viewport.TopLeftX = 0;
			viewport.TopLeftY = 0;
			viewport.Width = res.x;
			viewport.Height = res.y;

			window::devcon->RSSetViewports(1, &viewport);
		}

		void close()
		{
			window::swapchain->SetFullscreenState(FALSE, NULL);    // switch to windowed mode

			window::swapchain->Release();
			window::backbuffer->Release();
			window::dev->Release();
			window::devcon->Release();
		}

		void swapBuffers(window& hwnd)
		{
			window::swapchain->Present(0, 0);
		}

		void drawArrays(PrimitiveType mode, int first, int count)
		{

		}

		void drawArraysInstanced(PrimitiveType mode, int first, int count, int instanceCount)
		{

		}

		void drawIndexed(PrimitiveType mode, int count, DataType type, const void* indecies)
		{
			////// select which vertex buffer to display
			//unsigned int stride = sizeof(VERTEX);
			//unsigned int offset = 0;
			//window::devcon->IASetVertexBuffers(0, 1, &vBuffer.pVBuffer, &stride, &offset);

			//// select which primtive type we are using
			////window::devcon->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			//window::devcon->IASetPrimitiveTopology(static_cast<D3D11_PRIMITIVE_TOPOLOGY>(mode));

			//// draw the vertex buffer to the back buffer
			//window::devcon->Draw(count, 0);
		}

		void drawIndexdInstanced(PrimitiveType mode, int count, DataType type, const void* indecies, int instanceCount)
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
			window::devcon->ClearRenderTargetView(window::backbuffer, colorData);
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

		void createShader(shader* shader, const std::string& name, const shader_source& source)
		{
			shader->initialize(name, source);
		}

		texture_handle createTexture2D(texture* texture, const std::string& name, const std::string& filepath, texture_parameters params = { rendering::WrapMode::REPEAT ,rendering::WrapMode::REPEAT, rendering::FilterMode::LINEAR_MIPMAP_LINEAR, rendering::FilterMode::LINEAR })
		{
			return texture;
		}

		template<typename dataType>
		void createBuffer(buffer* buffer, TargetType target, UsageType usage, dataType* data = nullptr, int size = 0)
		{
			buffer->initialize(target, usage);
			if (data)
			{
				buffer->bufferData(data, size);
			}
		}
	};
}