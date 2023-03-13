#pragma once
#include <string>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
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
#include "rendering/data/texturehandle.hpp"
#include "rendering/data/interface/window.hpp"
#include "rendering/data/DirectX/buffer.hpp"
#include "rendering/data/DirectX/shader.hpp"

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
		ID3D11Buffer* pVBuffer;    // global

		// global
		ID3D11VertexShader* pVS;    // the vertex shader
		ID3D11PixelShader* pPS;     // the pixel shader

		ID3D11InputLayout* pLayout;    // global
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
			pVS->Release();
			pPS->Release();
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
			// select which vertex buffer to display
			unsigned int stride = sizeof(VERTEX);
			unsigned int offset = 0;
			devcon->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);

			// select which primtive type we are using
			devcon->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			// draw the vertex buffer to the back buffer
			devcon->Draw(3, 0);
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
			auto fileName = std::wstring(filepath.begin(), filepath.end());
			D3DX11CompileFromFile(fileName.c_str(), 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
			D3DX11CompileFromFile(fileName.c_str(), 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);

			// encapsulate both shaders into shader objects
			dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
			dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

			// set the shader objects
			devcon->VSSetShader(pVS, 0, 0);
			devcon->PSSetShader(pPS, 0, 0);

			// create the input layout object
			D3D11_INPUT_ELEMENT_DESC ied[] =
			{
				{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
			};

			dev->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
			devcon->IASetInputLayout(pLayout);
		}

		texture_handle createTexture2D(texture* texture, const std::string& name, const std::string& filepath, texture_parameters params = { GL_REPEAT ,GL_REPEAT,GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR })
		{
			return texture;
		}

		void createVertexBuffer()
		{
			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));

			bd.Usage = D3D11_USAGE_DYNAMIC;                // write access access by CPU and GPU
			bd.ByteWidth = sizeof(VERTEX) * 3;             // size is the VERTEX struct * 3
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;       // use as a vertex buffer
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;    // allow CPU to write in buffer

			dev->CreateBuffer(&bd, NULL, &pVBuffer);       // create the buffer

			// copy the vertices into the buffer
			D3D11_MAPPED_SUBRESOURCE ms;
			devcon->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);    // map the buffer
			memcpy(ms.pData, OurVertices, sizeof(OurVertices));                 // copy the data
			devcon->Unmap(pVBuffer, NULL);                                      // unmap the buffer
		}
	};
}