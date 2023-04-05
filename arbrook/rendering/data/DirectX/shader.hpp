#pragma once
#include <D3D11.h>
#include <D3DX11.h>
#include <D3DX10.h>
#include <D3Dcompiler.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")
#pragma comment(lib, "D3DCompiler.lib")

#include "rendering/data/shadersource.hpp"
#include "rendering/data/config.hpp"
#include Window_HPP_PATH

namespace rythe::rendering::internal
{
	enum ConstantBuffer
	{
		CB_Application,
		CB_Frame,
		CB_Object,
		NumConstantBuffers
	};

	struct shader
	{
	private:
		ID3D10Blob* VS, * PS;
		ID3D11VertexShader* pVS;    // the vertex shader
		ID3D11PixelShader* pPS;     // the pixel shader
		ID3D11InputLayout* pLayout;    // global

		ID3D11Buffer* constantBuffers[NumConstantBuffers];

		window& m_hwnd;
	public:
		unsigned int m_programId;
		std::string m_name;

		shader() = default;
		shader(shader* other, window& hwnd) : m_hwnd(hwnd)
		{
			m_programId = other->m_programId;
			m_name = other->m_name;
		}
		~shader()
		{
			pVS->Release();
			pPS->Release();
		}
		operator unsigned int() const { return m_programId; }

		void initialize(window& hwnd, const std::string& name, const shader_source& source)
		{
			compileShader(0, source.vertexSource);
			compileShader(1, source.fragSource);
			m_hwnd = hwnd;
			// encapsulate both shaders into shader objects
			m_hwnd.m_dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
			m_hwnd.m_dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

			// set the shader objects
			m_hwnd.m_devcon->VSSetShader(pVS, 0, 0);
			m_hwnd.m_devcon->PSSetShader(pPS, 0, 0);

			// create the input layout object
			D3D11_INPUT_ELEMENT_DESC ied[] =
			{
				{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0},
				{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0},
			};

			hwnd.m_dev->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
			hwnd.m_devcon->IASetInputLayout(pLayout);
		}

		void setUniform(const std::string& uniformName, math::vec4 value)
		{
			// Create the constant buffers for the variables defined in the vertex shader.
			D3D11_BUFFER_DESC constantBufferDesc;
			ZeroMemory(&constantBufferDesc, sizeof(D3D11_BUFFER_DESC));

			constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			constantBufferDesc.ByteWidth = sizeof(math::vec4);
			constantBufferDesc.CPUAccessFlags = 0;
			constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;

			m_hwnd.m_dev->CreateBuffer(&constantBufferDesc, nullptr, &constantBuffers[CB_Application]);
			m_hwnd.m_dev->CreateBuffer(&constantBufferDesc, nullptr, &constantBuffers[CB_Frame]);
			m_hwnd.m_dev->CreateBuffer(&constantBufferDesc, nullptr, &constantBuffers[CB_Object]);
		}

		void setUniform(const std::string& uniformName, math::vec3 value)
		{

		}

		void setUniform(const std::string& uniformName, math::vec2 value)
		{

		}

		void setUniform(const std::string& uniformName, float value)
		{

		}

		void setUniform(const std::string& uniformName, math::ivec4 value)
		{

		}

		void setUniform(const std::string& uniformName, math::ivec3 value)
		{

		}

		void setUniform(const std::string& uniformName, math::ivec2 value)
		{

		}

		void setUniform(const std::string& uniformName, int value)
		{

		}

	private:
		unsigned int compileShader(unsigned int type, const std::string& source)
		{
			if (type == 0)
			{
				D3DCompile(source.c_str(), source.length(), nullptr, nullptr, nullptr, "VShader", "vs_4_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &VS, nullptr);
			}
			else if (type == 1)
			{
				D3DCompile(source.c_str(), source.length(), nullptr, nullptr, nullptr, "PShader", "ps_4_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &PS, nullptr);
			}
			return 0;
		}
	};
}