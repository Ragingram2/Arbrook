#pragma once
#include <string>
#include <string_view>
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
		GLFWwindow* m_window;
	public:
		math::ivec2 m_resolution;
		std::string m_windowName;

		IDXGISwapChain* m_swapchain;             // the pointer to the swap chain interface
		ID3D11Device* m_dev;                     // the pointer to our Direct3D device interface
		ID3D11DeviceContext* m_devcon;           // the pointer to our Direct3D device context
		ID3D11RenderTargetView* m_backbuffer;    // global declaration
		ID3D11InfoQueue* m_infoQueue;
	public:
		window() = default;
		window(window& hwnd) 
		{
			m_resolution = hwnd.m_resolution;
			m_windowName = hwnd.m_windowName;
			m_window = hwnd.getWindow();
		}
		window(math::ivec2 res, const std::string& name) : m_resolution(res), m_windowName(name) { }

		GLFWwindow* getWindow()
		{
			return m_window;
		}

		void initialize(math::ivec2 res, const std::string& name)
		{
			m_resolution = res;
			m_windowName = name;
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

		void makeCurrent()
		{
			glfwMakeContextCurrent(m_window);
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