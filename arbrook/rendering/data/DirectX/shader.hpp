#pragma once
#include <unordered_map>

#include <D3D11.h>
#include <D3DX11.h>
#include <D3DX10.h>
#include <D3Dcompiler.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")
#pragma comment(lib, "D3DCompiler.lib")

#include "rendering/data/bufferhandle.hpp"
#include "rendering/data/shadersource.hpp"
#include "rendering/data/config.hpp"
#include Window_HPP_PATH
#include EnumTypes_HPP_PATH

namespace rythe::rendering::internal
{
	struct shader
	{
	private:
		window m_hwnd;
		ID3D11VertexShader* m_VS = nullptr;
		ID3D11PixelShader* m_PS = nullptr;
		std::unordered_map<std::string, buffer_handle> m_vsConstBuffers;
		std::unordered_map<std::string, buffer_handle> m_psConstBuffers;
	public:
		unsigned int programId;
		std::string name;

		ID3D10Blob* VS = nullptr;
		ID3D10Blob* PS = nullptr;

		shader() = default;
		shader(shader* other, window& hwnd) : m_hwnd(hwnd)
		{
			programId = other->programId;
			name = other->name;
		}
		~shader()
		{
			if (m_VS != nullptr)
				m_VS->Release();
			if (m_PS != nullptr)
				m_PS->Release();
		}
		operator unsigned int() const { return programId; }

		void initialize(window& hwnd, const std::string& name, const shader_source& source)
		{
			m_hwnd = hwnd;
			compileShader(ShaderType::VERTEX, source.vertexSource);
			compileShader(ShaderType::FRAGMENT, source.fragSource);

			m_hwnd.m_dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &m_VS);
			m_hwnd.m_dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &m_PS);
		}

		void bind()
		{
			m_hwnd.m_devcon->VSSetShader(m_VS, 0, 0);
			m_hwnd.m_devcon->PSSetShader(m_PS, 0, 0);

			std::vector<ID3D11Buffer*> buffers;
			for (auto& [name, handle] : m_vsConstBuffers)
			{
				buffers.push_back(handle.buffer->m_impl);
			}
			m_hwnd.m_devcon->VSSetConstantBuffers(0, m_vsConstBuffers.size(), buffers.data());

			for (auto& [name, handle] : m_psConstBuffers)
			{
				buffers.push_back(handle.buffer->m_impl);
			}
			m_hwnd.m_devcon->PSSetConstantBuffers(0, m_psConstBuffers.size(), buffers.data());
		}

		void addBuffer(ShaderType type, buffer_handle handle)
		{
			if (static_cast<internal::TargetType>(handle.getTargetType()) != TargetType::CONSTANT_BUFFER)
			{
				log::error("Buffer is not a constant buffer, this is not supported");
				return;
			}

			switch (type)
			{
			case ShaderType::VERTEX:
				m_vsConstBuffers.emplace(handle->getName(), handle);
				break;
			case ShaderType::FRAGMENT:
				m_psConstBuffers.emplace(handle->getName(), handle);
				break;
			default:
				log::error("Adding a constant buffer to shader type {} is not supported", STRINGIFY(type));
				break;
			}
		}

		template<typename elementType>
		void setData(const std::string& bufferName, elementType data[])
		{
			if (m_vsConstBuffers.count(bufferName) != 0)
			{
				m_vsConstBuffers[bufferName]->bufferData(data);
			}

			if (m_psConstBuffers.count(bufferName) != 0)
			{
				m_psConstBuffers[bufferName]->bufferData(data);
			}
		}

	private:
		unsigned int compileShader(ShaderType type, const std::string& source)
		{
			HRESULT hr;
			if (type == ShaderType::VERTEX)
			{
				hr = D3DCompile(source.c_str(), source.length(), nullptr, nullptr, nullptr, "VShader", "vs_4_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &VS, nullptr);
			}
			else if (type == ShaderType::FRAGMENT)
			{
				hr = D3DCompile(source.c_str(), source.length(), nullptr, nullptr, nullptr, "PShader", "ps_4_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &PS, nullptr);
			}

			if (FAILED(hr))
			{
				log::error("Shader Compilation failed");
			}
			return 0;
		}
	};
}