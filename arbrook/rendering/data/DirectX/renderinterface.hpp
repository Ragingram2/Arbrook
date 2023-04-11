#pragma once
#include <string>
#include <fstream>
#include <memory>
#include <stdio.h>

#include <D3D11.h>
#include <D3DX11.h>
#include <D3DX10.h>
#include <D3Dcompiler.h>
#include <DxErr.h>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")
#pragma comment (lib, "DxErr.lib")
#pragma comment (lib, "D3DCompiler.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")

#include "core/math/math.hpp"
#include "core/logging/logging.hpp"
#include "rendering/data/shadersource.hpp"
#include "rendering/data/texturehandle.hpp"
#include "rendering/data/config.hpp"

#include Window_HPP_PATH
#include Shader_HPP_PATH
#include Buffer_HPP_PATH

//#ifndef HR
//#define HR(x) \
//{ \
//	HRESULT hr = x;\
//	if(FAILED(hr)) \
//	{	\
//		log::error("Error Code: {}",L#x);\
//	}\
//}
//#endif
//#ifndef HR
//#define HR(x) x;
//#endif

namespace rythe::rendering::internal
{
	class RenderInterface
	{
	private:
		ID3D11InfoQueue* m_infoQueue;
		ID3D11RasterizerState* m_rasterizerState;
		window hwnd;
	public:
		void initialize(math::ivec2 res, const std::string& name)
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
			scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

			UINT creationFlags = D3D11_CREATE_DEVICE_DEBUG;

			auto hr = D3D11CreateDeviceAndSwapChain(NULL,
				D3D_DRIVER_TYPE_HARDWARE,
				NULL,
				creationFlags,
				NULL,
				NULL,
				D3D11_SDK_VERSION,
				&scd,
				&hwnd.m_swapchain,
				&hwnd.m_dev,
				NULL,
				&hwnd.m_devcon);

			if (FAILED(hr))
			{
				log::error("Something happened");
				__debugbreak();
			}

			ID3D11Texture2D* pBackBuffer;
			hr = hwnd.m_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			if (FAILED(hr))
			{
				log::error("Something happened");
				__debugbreak();
			}

			hr = hwnd.m_dev->CreateRenderTargetView(pBackBuffer, NULL, &hwnd.m_backbuffer);
			pBackBuffer->Release();
			if (FAILED(hr))
			{
				log::error("Something happened");
				__debugbreak();
			}

			hwnd.m_devcon->OMSetRenderTargets(1, &hwnd.m_backbuffer, NULL);

			//// Setup rasterizer state.
			//D3D11_RASTERIZER_DESC rasterizerDesc;
			//ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));

			//rasterizerDesc.AntialiasedLineEnable = FALSE;
			//rasterizerDesc.CullMode = D3D11_CULL_BACK;
			//rasterizerDesc.DepthBias = 0;
			//rasterizerDesc.DepthBiasClamp = 0.0f;
			//rasterizerDesc.DepthClipEnable = TRUE;
			//rasterizerDesc.FillMode = D3D11_FILL_SOLID;
			//rasterizerDesc.FrontCounterClockwise = FALSE;
			//rasterizerDesc.MultisampleEnable = FALSE;
			//rasterizerDesc.ScissorEnable = FALSE;
			//rasterizerDesc.SlopeScaledDepthBias = 0.0f;

			//// Create the rasterizer state object.
			//hr = hwnd.m_dev->CreateRasterizerState(&rasterizerDesc, &m_rasterizerState);
			//if (FAILED(hr))
			//{
			//	log::error("Something happened");
			//	__debugbreak();
			//}

			D3D11_VIEWPORT viewport;
			ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

			viewport.TopLeftX = 0;
			viewport.TopLeftY = 0;
			viewport.Width = res.x;
			viewport.Height = res.y;
			//viewport.MinDepth = 0;
			//viewport.MaxDepth = 1;

			hwnd.m_devcon->RSSetViewports(1, &viewport);

			hr = hwnd.m_dev->QueryInterface(__uuidof(ID3D11InfoQueue), (void**)&m_infoQueue);
			if (FAILED(hr))
			{
				log::error("Something happened");
				__debugbreak();
			}

			//m_infoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR,true);
		}

		void close()
		{
			hwnd.m_swapchain->SetFullscreenState(FALSE, NULL);

			hwnd.m_swapchain->Release();
			hwnd.m_backbuffer->Release();
			hwnd.m_dev->Release();
			hwnd.m_devcon->Release();
		}

		GLFWwindow* getWindow()
		{
			return hwnd.getWindow();
		}

		window& getHwnd()
		{
			return hwnd;
		}

		void makeCurrent()
		{
			hwnd.makeCurrent();
		}

		void setSwapInterval(int interval)
		{
			hwnd.setSwapInterval(interval);
		}

		bool shouldWindowClose()
		{
			return hwnd.shouldClose();
		}

		void pollEvents()
		{
			hwnd.pollEvents();
		}

		void swapBuffers()
		{
			hwnd.m_swapchain->Present(0, 0);
		}

		void drawArrays(PrimitiveType mode, unsigned int startVertex, unsigned int vertexCount)
		{

		}

		void drawArraysInstanced(PrimitiveType mode, unsigned int vertexCount, unsigned int instanceCount, unsigned int startVertex, unsigned int startInstance)
		{

		}

		void drawIndexed(PrimitiveType mode, unsigned int indexCount, unsigned int startIndex, unsigned int baseVertex)
		{
			hwnd.m_devcon->IASetPrimitiveTopology(static_cast<D3D11_PRIMITIVE_TOPOLOGY>(mode));
			hwnd.m_devcon->DrawIndexed(indexCount, startIndex, baseVertex);
		}

		void drawIndexdInstanced(PrimitiveType mode, unsigned int indexCount, unsigned int instanceCount, unsigned int startIndex, unsigned int baseVertex, unsigned int startInstance)
		{

		}

		void bind(shader* shader)
		{
			hwnd.m_devcon->VSSetShader(shader->m_VS, 0, 0);
			hwnd.m_devcon->PSSetShader(shader->m_PS, 0, 0);
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
			hwnd.m_devcon->ClearRenderTargetView(hwnd.m_backbuffer, colorData);
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
			shader->initialize(hwnd, name, source);
		}

		texture_handle createTexture2D(texture* texture, const std::string& name, const std::string& filepath, texture_parameters params = { rendering::WrapMode::REPEAT ,rendering::WrapMode::REPEAT, rendering::FilterMode::LINEAR_MIPMAP_LINEAR, rendering::FilterMode::LINEAR })
		{
			return texture;
		}

		template<typename elementType, typename dataType = elementType>
		void createBuffer(buffer* buffer, TargetType target, UsageType usage, elementType* data = nullptr, int size = 0)
		{
			buffer->initialize(target, usage);
			if (data)
			{
				buffer->bufferData<elementType,dataType>(hwnd, data, size);
			}
		}

		void checkError()
		{

			UINT64 message_count = m_infoQueue->GetNumStoredMessages();

			for (UINT64 i = 0; i < message_count; i++) {
				SIZE_T message_size = 0;
				m_infoQueue->GetMessage(i, nullptr, &message_size);

				D3D11_MESSAGE* message = (D3D11_MESSAGE*)malloc(message_size);
				m_infoQueue->GetMessage(i, message, &message_size);
				switch (message->Severity)
				{
				case D3D11_MESSAGE_SEVERITY_CORRUPTION:
					log::fatal("DX11: {}", message->pDescription);
					break;
				case D3D11_MESSAGE_SEVERITY_ERROR:
					log::error("DX11: {}", message->pDescription);
					break;
				case D3D11_MESSAGE_SEVERITY_INFO:
					log::info("DX11: {}", message->pDescription);
					break;
				case D3D11_MESSAGE_SEVERITY_WARNING:
					log::warn("DX11: {}", message->pDescription);
					break;
				}

				free(message);
			}
			m_infoQueue->ClearStoredMessages();
		}
	};
}