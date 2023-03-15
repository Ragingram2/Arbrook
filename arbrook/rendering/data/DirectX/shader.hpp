#pragma once
#include <D3D11.h>
#include <D3Dx11.h>
#include <D3Dx10.h>
#include <d3dcompiler.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")
#pragma comment(lib, "D3DCompiler.lib")

#include "core/math/math.hpp"
#include "rendering/data/shadersource.hpp"
#include "rendering/data/config.hpp"
#include Window_HPP_PATH

namespace rythe::rendering::internal
{
	struct shader
	{
	private:
		ID3D10Blob* VS, * PS;
		ID3D11VertexShader* pVS;    // the vertex shader
		ID3D11PixelShader* pPS;     // the pixel shader
		ID3D11InputLayout* pLayout;    // global
	public:
		unsigned int m_programId;
		std::string m_name;

		shader() = default;
		shader(shader* other)
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

		void initialize(const std::string& name, const shader_source& source)
		{
			compileShader(0, source.vertexSource);
			compileShader(1, source.fragSource);

			// encapsulate both shaders into shader objects
			window::dev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
			window::dev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

			// set the shader objects
			window::devcon->VSSetShader(pVS, 0, 0);
			window::devcon->PSSetShader(pPS, 0, 0);

			// create the input layout object
			D3D11_INPUT_ELEMENT_DESC ied[] =
			{
				{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
				{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
			};

			window::dev->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
			window::devcon->IASetInputLayout(pLayout);
		}

		void setUniform(const std::string& uniformName, math::vec4 value)
		{

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