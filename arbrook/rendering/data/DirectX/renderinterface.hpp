#pragma once
#include <string>
#include <fstream>
#include <memory>
#include <stdio.h>

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>


#include "core/math/math.hpp"
#include "core/logging/logging.hpp"
#include "rendering/data/DirectX/dx11includes.hpp"
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
	private:
		ID3D11RasterizerState* m_rasterizerState = nullptr;
		float colorData[4];
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

			HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL,
				D3D_DRIVER_TYPE_HARDWARE,
				NULL,
				creationFlags,
				NULL,
				NULL,
				D3D11_SDK_VERSION,
				&scd,
				&hwnd.swapchain,
				&hwnd.dev,
				NULL,
				&hwnd.devcon);
			if (FAILED(hr))
			{
				log::error("Initializing the device and swapchain failed");
			}

			ID3D11Texture2D* pBackBuffer;
			hr = hwnd.swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
			if (FAILED(hr))
			{
				log::error("Retrieving the backbuffer failed");
			}

			hr = hwnd.dev->CreateRenderTargetView(pBackBuffer, NULL, &hwnd.backbuffer);
			if (FAILED(hr))
			{
				log::error("Creating a render target view failed");
			}
			pBackBuffer->Release();

			D3D11_TEXTURE2D_DESC depthStencilDesc;

			depthStencilDesc.Width = res.x;
			depthStencilDesc.Height = res.y;
			depthStencilDesc.MipLevels = 1;
			depthStencilDesc.ArraySize = 1;
			depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			depthStencilDesc.SampleDesc.Count = 1;
			depthStencilDesc.SampleDesc.Quality = 0;
			depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
			depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			depthStencilDesc.CPUAccessFlags = 0;
			depthStencilDesc.MiscFlags = 0;

			//Create the Depth/Stencil View
			hwnd.dev->CreateTexture2D(&depthStencilDesc, NULL, &hwnd.depthStencilBuffer);
			hwnd.dev->CreateDepthStencilView(hwnd.depthStencilBuffer, NULL, &hwnd.depthStencil);

			hwnd.devcon->OMSetRenderTargets(1, &hwnd.backbuffer, hwnd.depthStencil);

			// Setup rasterizer state.
			D3D11_RASTERIZER_DESC rasterizerDesc;
			ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));

			rasterizerDesc.AntialiasedLineEnable = FALSE;
			rasterizerDesc.CullMode = D3D11_CULL_BACK;
			rasterizerDesc.DepthBias = 0;
			rasterizerDesc.DepthBiasClamp = 0.0f;
			rasterizerDesc.DepthClipEnable = TRUE;
			rasterizerDesc.FillMode = D3D11_FILL_SOLID;
			rasterizerDesc.FrontCounterClockwise = TRUE;
			rasterizerDesc.MultisampleEnable = FALSE;
			rasterizerDesc.ScissorEnable = FALSE;
			rasterizerDesc.SlopeScaledDepthBias = 0.0f;

			// Create the rasterizer state object.
			hr = hwnd.dev->CreateRasterizerState(&rasterizerDesc, &m_rasterizerState);

			hwnd.devcon->RSSetState(m_rasterizerState);

			setViewport();

#ifdef _DEBUG
			hr = hwnd.dev->QueryInterface(__uuidof(ID3D11InfoQueue), (void**)&hwnd.infoQueue);
			if (FAILED(hr))
			{
				log::error("Retrieving the info queue failed");
			}
			//m_infoQueue->SetBreakOnSeverity(D3D11_MESSAGE_SEVERITY_ERROR,true);
#endif

		}

		void close()
		{
			hwnd.swapchain->SetFullscreenState(FALSE, NULL);

			hwnd.swapchain->Release();
			hwnd.backbuffer->Release();
			hwnd.dev->Release();
			hwnd.devcon->Release();
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
			hwnd.swapchain->Present(1, 0);
		}

		void drawArrays(PrimitiveType mode, unsigned int startVertex, unsigned int vertexCount)
		{
			hwnd.devcon->IASetPrimitiveTopology(static_cast<D3D11_PRIMITIVE_TOPOLOGY>(mode));
			hwnd.devcon->Draw(vertexCount, startVertex);
		}

		void drawArraysInstanced(PrimitiveType mode, unsigned int vertexCount, unsigned int instanceCount, unsigned int startVertex, unsigned int startInstance)
		{
			hwnd.devcon->IASetPrimitiveTopology(static_cast<D3D11_PRIMITIVE_TOPOLOGY>(mode));
			hwnd.devcon->DrawInstanced(vertexCount, instanceCount, startVertex, startInstance);
		}

		void drawIndexed(PrimitiveType mode, unsigned int indexCount, unsigned int startIndex, unsigned int baseVertex)
		{
			hwnd.devcon->IASetPrimitiveTopology(static_cast<D3D11_PRIMITIVE_TOPOLOGY>(mode));
			hwnd.devcon->DrawIndexed(indexCount, startIndex, baseVertex);
		}

		void drawIndexedInstanced(PrimitiveType mode, unsigned int indexCount, unsigned int instanceCount, unsigned int startIndex, unsigned int baseVertex, unsigned int startInstance)
		{
			hwnd.devcon->IASetPrimitiveTopology(static_cast<D3D11_PRIMITIVE_TOPOLOGY>(mode));
			hwnd.devcon->DrawIndexedInstanced(indexCount, instanceCount, startIndex, baseVertex, startInstance);
		}

		void clear(internal::ClearBit flags)
		{
			hwnd.devcon->ClearDepthStencilView(hwnd.depthStencil, static_cast<D3D11_CLEAR_FLAG>(flags), 1.f, 0);
			if (flags == internal::ClearBit::COLOR || flags == internal::ClearBit::COLOR_DEPTH || flags == internal::ClearBit::COLOR_DEPTH_STENCIL)
				hwnd.devcon->ClearRenderTargetView(hwnd.backbuffer, colorData);
		}

		void setClearColor(math::vec4 color)
		{
			colorData[0] = color.r;
			colorData[1] = color.g;
			colorData[2] = color.b;
			colorData[3] = color.a;
		}

		void setViewport(float numViewPorts = 1, float topLeftX = 0, float topLeftY = 0, float width = 0, float height = 0, float minDepth = -1, float maxDepth = 1)
		{
			if (width == 0 && height == 0)
			{
				width = hwnd.m_resolution.x;
				height = hwnd.m_resolution.y;
			}

			D3D11_VIEWPORT viewport;
			ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

			viewport.TopLeftX = topLeftX;
			viewport.TopLeftY = topLeftY;
			viewport.Width = width;
			viewport.Height = height;
			viewport.MinDepth = minDepth;
			viewport.MaxDepth = maxDepth;

			hwnd.devcon->RSSetViewports(numViewPorts, &viewport);

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

		void createTexture2D(texture* texture, const std::string& name, const std::string& filepath, texture_parameters params = { rendering::WrapMode::REPEAT ,rendering::WrapMode::REPEAT, rendering::FilterMode::LINEAR,rendering::FormatType::RGBA8UN, 1 }, bool generateMipMaps = false)
		{
			texture->initialize(hwnd, TargetType::TEXTURE2D, UsageType::IMMUTABLE, params, generateMipMaps);
			texture->loadData(filepath);
		}

		template<typename elementType>
		void createBuffer(buffer* buffer, TargetType target, UsageType usage, elementType* data = nullptr, int size = 1)
		{
			buffer->initialize<elementType>(hwnd, target, usage, size);
			if (data)
			{
				buffer->bufferData(data);
			}
		}

		void checkError()
		{
			UINT64 message_count = hwnd.infoQueue->GetNumStoredMessages();

			for (UINT64 i = 0; i < message_count; i++) {
				SIZE_T message_size = 0;
				hwnd.infoQueue->GetMessage(i, nullptr, &message_size);

				D3D11_MESSAGE* message = (D3D11_MESSAGE*)malloc(message_size);
				hwnd.infoQueue->GetMessage(i, message, &message_size);
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
			hwnd.infoQueue->ClearStoredMessages();
		}
	};
}