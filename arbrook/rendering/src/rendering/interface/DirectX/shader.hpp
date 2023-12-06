#pragma once
#include <unordered_map>

#include <rsl/logging>

#include "rendering/data/bufferhandle.hpp"
#include "rendering/data/shadersource.hpp"
#include "rendering/cache/windowprovider.hpp"
#include "rendering/interface/DirectX/dx11includes.hpp"
#include "rendering/interface/DirectX/shadercompiler.hpp"
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
		ID3D11GeometryShader* m_GS = nullptr;
		ID3D11HullShader* m_HS = nullptr;
		ID3D11ComputeShader* m_CS = nullptr;
		std::unordered_map<std::string, buffer_handle> m_constBuffers;
		window_handle m_windowHandle;
	public:
		unsigned int programId;
		std::string name;

		ID3DBlob* VS = nullptr;
		ID3DBlob* PS = nullptr;
		ID3DBlob* GS = nullptr;
		ID3DBlob* HS = nullptr;
		ID3DBlob* CS = nullptr;

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
			m_windowHandle = WindowProvider::get(0);
			ShaderCompiler::initialize();
			VS = ShaderCompiler::compile(ShaderType::VERTEX,source);
			//compileShader(ShaderType::VERTEX, source.sources[0].second);
			m_windowHandle->checkError();
			PS = ShaderCompiler::compile(ShaderType::FRAGMENT, source);
			//compileShader(ShaderType::FRAGMENT, source.sources[1].second);
			m_windowHandle->checkError();

			m_windowHandle->dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &m_VS);
			m_windowHandle->dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &m_PS);
		}

		void bind()
		{
			m_windowHandle->devcon->VSSetShader(m_VS, 0, 0);
			m_windowHandle->devcon->PSSetShader(m_PS, 0, 0);

			for (auto& [name, handle] : m_constBuffers)
			{
				handle->bind();
			}
		}

		void addBuffer(buffer_handle handle)
		{
			if (static_cast<internal::TargetType>(handle->getTargetType()) != TargetType::CONSTANT_BUFFER)
			{
				log::error("Buffer is not a constant buffer, this is not supported");
				return;
			}

			if (!m_constBuffers.count(handle->getName()))
				m_constBuffers.emplace(handle->getName(), handle);
		}

		template<typename elementType>
		void setData(const std::string& bufferName, elementType data[])
		{
			bool dataSet = false;
			if (m_constBuffers.count(bufferName) != 0)
			{
				m_constBuffers[bufferName]->bufferData(data);
				dataSet = true;
			}

			if (!dataSet)
				log::error("No data was buffered, because the buffer {} was not added or does not exist", bufferName);
		}

		void release()
		{
			clearBuffers();
		}

		void clearBuffers()
		{
			m_constBuffers.clear();
		}

	private:
//		unsigned int compileShader(ShaderType type, const std::string& source)
//		{
//			HRESULT hr;
//			ID3DBlob* error;
//
//			UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
//#if defined( DEBUG ) || defined( _DEBUG )
//			flags |= D3DCOMPILE_DEBUG;
//#endif
//			if (type == ShaderType::VERTEX)
//			{
//				hr = D3DCompile(source.c_str(), source.length(), nullptr, nullptr, nullptr, "VShader", "vs_4_0", flags, 0, &VS, &error);
//				if (FAILED(hr))
//				{
//					log::error("Vertex Shader Compilation failed");
//					if (error)
//					{
//						log::error((char*)error->GetBufferPointer());
//					}
//					m_windowHandle->checkError();
//				}
//			}
//			else if (type == ShaderType::FRAGMENT)
//			{
//				hr = D3DCompile(source.c_str(), source.length(), nullptr, nullptr, nullptr, "PShader", "ps_4_0", flags, 0, &PS, &error);
//				if (FAILED(hr))
//				{
//					log::error("Fragment Shader Compilation failed");
//					if (error)
//					{
//						log::error((char*)error->GetBufferPointer());
//					}
//					m_windowHandle->checkError();
//				}
//			}
//
//			return 0;
//		}
	};
}