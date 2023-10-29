#pragma once
#include <unordered_map>

#include <rsl/logging>

#include "rendering/interface/DirectX/dx11includes.hpp"
#include "rendering/data/bufferhandle.hpp"
#include "rendering/data/shadersource.hpp"
#include "rendering/interface/definitions/window.hpp"
#include "rendering/interface/config.hpp"
#include EnumTypes_HPP_PATH

namespace rythe::rendering::internal
{
	struct shader
	{
	private:
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
		shader(shader* other)
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

		void initialize(const std::string& name, const shader_source& source)
		{
			compileShader(ShaderType::VERTEX, source.vertexSource);
			hwnd.checkError();
			compileShader(ShaderType::FRAGMENT, source.fragSource);
			hwnd.checkError();

			hwnd.dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &m_VS);
			hwnd.dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &m_PS);
		}

		void bind()
		{
			hwnd.devcon->VSSetShader(m_VS, 0, 0);
			hwnd.devcon->PSSetShader(m_PS, 0, 0);

			std::vector<ID3D11Buffer*> buffers;
			for (auto& [name, handle] : m_vsConstBuffers)
			{
				buffers.push_back(handle.m_data->m_impl);
			}
			hwnd.devcon->VSSetConstantBuffers(0, m_vsConstBuffers.size(), buffers.data());

			for (auto& [name, handle] : m_psConstBuffers)
			{
				buffers.push_back(handle.m_data->m_impl);
			}
			hwnd.devcon->PSSetConstantBuffers(0, m_psConstBuffers.size(), buffers.data());
		}

		void addBuffer(ShaderType type, buffer_handle handle)
		{
			if (static_cast<internal::TargetType>(handle->getTargetType()) != TargetType::CONSTANT_BUFFER)
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
				log::error("Adding a constant buffer to shader type {} is not supported", RYTHE_STRINGIFY(type));
				break;
			}
		}

		template<typename elementType>
		void setData(const std::string& bufferName, elementType data[])
		{
			bool dataSet = false;
			if (m_vsConstBuffers.count(bufferName) != 0)
			{
				m_vsConstBuffers[bufferName]->bufferData(data);
				dataSet = true;
			}

			if (m_psConstBuffers.count(bufferName) != 0)
			{
				m_psConstBuffers[bufferName]->bufferData(data);
				dataSet = true;
			}

			if (!dataSet)
				log::error("No data was buffered, because the buffer {} was not added or does not exist",bufferName);
		}

		void release()
		{

			clearBuffers();
		}

		void clearBuffers()
		{
			m_vsConstBuffers.clear();
			m_psConstBuffers.clear();
		}

	private:
		unsigned int compileShader(ShaderType type, const std::string& source)
		{
			HRESULT hr;
			ID3DBlob* error;

			UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
			flags |= D3DCOMPILE_DEBUG;
#endif
			if (type == ShaderType::VERTEX)
			{
				hr = D3DCompile(source.c_str(), source.length(), nullptr, nullptr, nullptr, "VShader", "vs_4_0", flags, 0, &VS, &error);
				if (FAILED(hr))
				{
					log::error("Vertex Shader Compilation failed");
					if (error)
					{
						log::error((char*)error->GetBufferPointer());
					}
					hwnd.checkError();
				}
			}
			else if (type == ShaderType::FRAGMENT)
			{
				hr = D3DCompile(source.c_str(), source.length(), nullptr, nullptr, nullptr, "PShader", "ps_4_0", flags, 0, &PS, &error);
				if (FAILED(hr))
				{
					log::error("Fragment Shader Compilation failed");
					if (error)
					{
						log::error((char*)error->GetBufferPointer());
					}
					hwnd.checkError();
				}
			}

			return 0;
		}
	};
}