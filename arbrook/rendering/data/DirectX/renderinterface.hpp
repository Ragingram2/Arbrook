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

#ifdef _DEBUG
#define CHECKERROR(hr,text,func) if(FAILED(hr))  { log::error(text); func;}
#else
#define CHECKERROR(hr,text,func)
#endif

namespace rythe::rendering::internal
{
	class RenderInterface
	{
	private:
		ID3D11RasterizerState* m_rasterizerState = nullptr;
		ID3D11DepthStencilState* m_depthStencilState = nullptr;
		ID3D11Texture2D* m_backBuffer = nullptr;
		D3D11_VIEWPORT m_viewport;
		DXGI_SWAP_CHAIN_DESC m_swapChainDesc;
		D3D11_TEXTURE2D_DESC m_depthTexDesc;
		D3D11_RASTERIZER_DESC m_rasterizerDesc;
		D3D11_DEPTH_STENCIL_DESC m_depthStencilDesc;
		D3D11_DEPTH_STENCIL_VIEW_DESC m_depthStencilViewDesc;
		float m_colorData[4];
		window m_hwnd;
	public:
		void initialize(math::ivec2 res, const std::string& name)
		{
			log::debug("Initializing DX11");
			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
			m_hwnd.initialize(res, name);

			ZeroMemory(&m_swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

			m_swapChainDesc.BufferCount = 1;                                    // one back buffer
			m_swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;     // use 32-bit color
			m_swapChainDesc.BufferDesc.Width = res.x;                    // set the back buffer width
			m_swapChainDesc.BufferDesc.Height = res.y;                  // set the back buffer height
			m_swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;      // how swap chain is to be used
			m_swapChainDesc.OutputWindow = glfwGetWin32Window(m_hwnd.getWindow());                                // the window to be used
			m_swapChainDesc.SampleDesc.Count = 1;                               // how many multisamples
			m_swapChainDesc.Windowed = TRUE;                                    // windowed/full-screen mode
			m_swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

			UINT creationFlags = D3D11_CREATE_DEVICE_DEBUG;

			HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL,
				D3D_DRIVER_TYPE_HARDWARE,
				NULL,
				creationFlags,
				NULL,
				NULL,
				D3D11_SDK_VERSION,
				&m_swapChainDesc,
				&m_hwnd.swapchain,
				&m_hwnd.dev,
				NULL,
				&m_hwnd.devcon);

#ifdef _DEBUG
			hr = m_hwnd.dev->QueryInterface(__uuidof(ID3D11InfoQueue), (void**)&m_hwnd.infoQueue);
			CHECKERROR(hr, "Retrieving the info queue failed", checkError());
#endif

			hr = m_hwnd.swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_backBuffer);
			CHECKERROR(hr, "Retrieving the backbuffer failed", checkError());

			hr = m_hwnd.dev->CreateRenderTargetView(m_backBuffer, NULL, &m_hwnd.backbuffer);
			CHECKERROR(hr, "Creating a render target view failed", checkError());

			m_backBuffer->Release();

			ZeroMemory(&m_depthTexDesc, sizeof(D3D11_TEXTURE2D_DESC));

			m_depthTexDesc.Width = res.x;
			m_depthTexDesc.Height = res.y;
			m_depthTexDesc.MipLevels = 1;
			m_depthTexDesc.ArraySize = 1;
			m_depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			m_depthTexDesc.SampleDesc.Count = m_swapChainDesc.SampleDesc.Count;
			m_depthTexDesc.SampleDesc.Quality = m_swapChainDesc.SampleDesc.Quality;
			m_depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
			m_depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			m_depthTexDesc.CPUAccessFlags = 0;
			m_depthTexDesc.MiscFlags = 0;

			hr = m_hwnd.dev->CreateTexture2D(&m_depthTexDesc, NULL, &m_hwnd.depthStencilBuffer);
			CHECKERROR(hr, "Creating the depth texture failed", checkError());

			ZeroMemory(&m_depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));

			//m_depthStencilDesc.DepthEnable = true;
			//m_depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			//m_depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
			//depthStencilDesc.StencilEnable = false;
			//depthStencilDesc.StencilReadMask = 0xFF;
			//depthStencilDesc.StencilWriteMask = 0xFF;
			//depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			//depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
			//depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			//depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
			//depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			//depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
			//depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			//depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

			hr = m_hwnd.dev->CreateDepthStencilState(&m_depthStencilDesc, &m_depthStencilState);
			CHECKERROR(hr, "Creating the depth stencil state failed", checkError());

			m_hwnd.devcon->OMSetDepthStencilState(m_depthStencilState, 1);

			ZeroMemory(&m_depthStencilViewDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));

			m_depthStencilViewDesc.Format = m_depthTexDesc.Format;
			m_depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;

			hr = m_hwnd.dev->CreateDepthStencilView(m_hwnd.depthStencilBuffer, &m_depthStencilViewDesc, &m_hwnd.depthStencilView);
			CHECKERROR(hr, "Creating the depth stencil view failed", checkError());

			m_hwnd.devcon->OMSetRenderTargets(1, &m_hwnd.backbuffer, m_hwnd.depthStencilView);

			ZeroMemory(&m_rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));

			m_rasterizerDesc.AntialiasedLineEnable = FALSE;
			m_rasterizerDesc.CullMode = D3D11_CULL_BACK;
			m_rasterizerDesc.DepthBias = 0;
			m_rasterizerDesc.DepthBiasClamp = 0.0f;
			m_rasterizerDesc.DepthClipEnable = TRUE;
			m_rasterizerDesc.FillMode = D3D11_FILL_SOLID;
			m_rasterizerDesc.FrontCounterClockwise = TRUE;
			m_rasterizerDesc.MultisampleEnable = FALSE;
			m_rasterizerDesc.ScissorEnable = FALSE;
			m_rasterizerDesc.SlopeScaledDepthBias = 0.0f;

			// Create the rasterizer state object.
			hr = m_hwnd.dev->CreateRasterizerState(&m_rasterizerDesc, &m_rasterizerState);
			CHECKERROR(hr, "Creating rasterizer state failed", checkError());

			m_hwnd.devcon->RSSetState(m_rasterizerState);

			setViewport(1, 0, 0, res.x, res.y);

		}

		void close()
		{
			m_hwnd.swapchain->SetFullscreenState(FALSE, NULL);

			m_hwnd.swapchain->Release();
			m_hwnd.backbuffer->Release();
			m_hwnd.dev->Release();
			m_hwnd.devcon->Release();
		}

		GLFWwindow* getWindow()
		{
			return m_hwnd.getWindow();
		}

		window& getHwnd()
		{
			return m_hwnd;
		}

		void makeCurrent()
		{
			m_hwnd.makeCurrent();
		}

		void setSwapInterval(int interval)
		{
			m_hwnd.setSwapInterval(interval);
		}

		bool shouldWindowClose()
		{
			return m_hwnd.shouldClose();
		}

		void pollEvents()
		{
			m_hwnd.pollEvents();
		}

		void swapBuffers()
		{
			m_hwnd.swapchain->Present(1, 0);
		}

		void drawArrays(PrimitiveType mode, unsigned int startVertex, unsigned int vertexCount)
		{
			m_hwnd.devcon->IASetPrimitiveTopology(static_cast<D3D11_PRIMITIVE_TOPOLOGY>(mode));
			m_hwnd.devcon->Draw(vertexCount, startVertex);
		}

		void drawArraysInstanced(PrimitiveType mode, unsigned int vertexCount, unsigned int instanceCount, unsigned int startVertex, unsigned int startInstance)
		{
			m_hwnd.devcon->IASetPrimitiveTopology(static_cast<D3D11_PRIMITIVE_TOPOLOGY>(mode));
			m_hwnd.devcon->DrawInstanced(vertexCount, instanceCount, startVertex, startInstance);
		}

		void drawIndexed(PrimitiveType mode, unsigned int indexCount, unsigned int startIndex, unsigned int baseVertex)
		{
			m_hwnd.devcon->IASetPrimitiveTopology(static_cast<D3D11_PRIMITIVE_TOPOLOGY>(mode));
			m_hwnd.devcon->DrawIndexed(indexCount, startIndex, baseVertex);
		}

		void drawIndexedInstanced(PrimitiveType mode, unsigned int indexCount, unsigned int instanceCount, unsigned int startIndex, unsigned int baseVertex, unsigned int startInstance)
		{
			m_hwnd.devcon->IASetPrimitiveTopology(static_cast<D3D11_PRIMITIVE_TOPOLOGY>(mode));
			m_hwnd.devcon->DrawIndexedInstanced(indexCount, instanceCount, startIndex, baseVertex, startInstance);
		}

		void clear(internal::ClearBit flags)
		{
			m_hwnd.devcon->ClearDepthStencilView(m_hwnd.depthStencilView, static_cast<D3D11_CLEAR_FLAG>(flags), 1.f, 0);
			if (flags == internal::ClearBit::COLOR || flags == internal::ClearBit::COLOR_DEPTH || flags == internal::ClearBit::COLOR_DEPTH_STENCIL)
				m_hwnd.devcon->ClearRenderTargetView(m_hwnd.backbuffer, m_colorData);
		}

		void setClearColor(math::vec4 color)
		{
			m_colorData[0] = color.r;
			m_colorData[1] = color.g;
			m_colorData[2] = color.b;
			m_colorData[3] = color.a;
		}

		void setViewport(float numViewPorts = 1, float topLeftX = 0, float topLeftY = 0, float width = 0, float height = 0, float minDepth = 0, float maxDepth = 1)
		{
			if (width == 0 && height == 0)
			{
				width = m_hwnd.m_resolution.x;
				height = m_hwnd.m_resolution.y;
			}

			ZeroMemory(&m_viewport, sizeof(D3D11_VIEWPORT));

			m_viewport.TopLeftX = topLeftX;
			m_viewport.TopLeftY = topLeftY;
			m_viewport.Width = width;
			m_viewport.Height = height;
			m_viewport.MinDepth = minDepth;
			m_viewport.MaxDepth = maxDepth;

			m_hwnd.devcon->RSSetViewports(numViewPorts, &m_viewport);

		}

		void enableDepthTest()
		{
			m_depthStencilDesc.DepthEnable = true;
		}

		void disableDepthTest()
		{
			m_depthStencilDesc.DepthEnable = false;
		}

		void enableDepthWrite()
		{
			m_depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		}

		void disableDepthWrite()
		{
			m_depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		}

		void setDepthFunction(internal::DepthFuncs function)
		{
			m_depthStencilDesc.DepthFunc = static_cast<D3D11_COMPARISON_FUNC>(function);
		}

		void enableStencilTest()
		{
			m_depthStencilDesc.StencilEnable = true;
		}

		void disableStencilTest()
		{
			m_depthStencilDesc.StencilEnable = false;
		}

		//m_depthStencilDesc.DepthEnable = true;
			//m_depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
			//m_depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
			//depthStencilDesc.StencilEnable = false;
			//depthStencilDesc.StencilReadMask = 0xFF;
			//depthStencilDesc.StencilWriteMask = 0xFF;
			//depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			//depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
			//depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			//depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
			//depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
			//depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
			//depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
			//depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		void setStencilOp(int face, StencilOp fail, StencilOp  zfail, StencilOp  zpass)
		{

		}

		void setStencilFunc(DepthFuncs func, unsigned int  ref, unsigned int mask)
		{

		}

		void updateDepthStencil()
		{
			log::info("Updating Depth Stencil");
			HRESULT hr = m_hwnd.dev->CreateDepthStencilState(&m_depthStencilDesc, &m_depthStencilState);
			CHECKERROR(hr, "Creating the depth stencil state failed", checkError());

			m_hwnd.devcon->OMSetDepthStencilState(m_depthStencilState, 1);
		}

		//createVAO();

		void createShader(shader* shader, const std::string& name, const shader_source& source)
		{
			shader->initialize(m_hwnd, name, source);
		}

		void createTexture2D(texture* texture, const std::string& name, const std::string& filepath, texture_parameters params = { rendering::WrapMode::REPEAT ,rendering::WrapMode::REPEAT, rendering::FilterMode::LINEAR,rendering::FormatType::RGBA8UN, 1 }, bool generateMipMaps = false)
		{
			texture->initialize(m_hwnd, TargetType::TEXTURE2D, UsageType::IMMUTABLE, params, generateMipMaps);
			texture->loadData(filepath);
		}

		template<typename elementType>
		void createBuffer(buffer* buffer, TargetType target, UsageType usage, elementType* data = nullptr, int size = 1)
		{
			buffer->initialize<elementType>(m_hwnd, target, usage, size);
			if (data)
			{
				buffer->bufferData(data);
			}
		}

		void checkError()
		{
			UINT64 message_count = m_hwnd.infoQueue->GetNumStoredMessages();

			for (UINT64 i = 0; i < message_count; i++) {
				SIZE_T message_size = 0;
				m_hwnd.infoQueue->GetMessage(i, nullptr, &message_size);

				D3D11_MESSAGE* message = (D3D11_MESSAGE*)malloc(message_size);
				m_hwnd.infoQueue->GetMessage(i, message, &message_size);
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
			m_hwnd.infoQueue->ClearStoredMessages();
		}
	};
}