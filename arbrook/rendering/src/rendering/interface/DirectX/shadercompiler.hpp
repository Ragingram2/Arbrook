#pragma once
#include <filesystem>

#include <d3d12shader.h>
#include <DxErr.h>
#include <dxcerrors.h>
#include <dxcapi.h>
#pragma comment(lib, "dxcompiler.lib")

#include <rsl/logging>
#include <rsl/primitives>

#include "rendering/interface/config.hpp"
#include "rendering/data/shadersource.hpp"
#include "rendering/cache/windowprovider.hpp"


namespace rythe::rendering::internal
{
	struct shader;

	class ShaderCompiler
	{
	private:
		static bool initialized;
		static window_handle m_windowHandle;
	public:
		static void initialize()
		{
			if (initialized) return;
			m_windowHandle = m_windowHandle = WindowProvider::get(0);
			initialized = true;
		}

		static ID3DBlob* compile(ShaderType type, shader_source source)
		{
			std::string profile;
			switch (static_cast<ShaderType>(type))
			{
			case ShaderType::VERTEX:
				profile = "vs_4_0";
				break;
			case ShaderType::FRAGMENT:
				profile = "ps_4_0";
				break;
			case ShaderType::GEOMETRY:
				profile = "gs_4_0";
				break;
			case ShaderType::HULL:
				profile = "hs_4_0";
				break;
			case ShaderType::COMPUTE:
				profile = "cs_4_0";
				break;
			}
			std::string file{ std::format("{}-{}", source.fileName, profile) };

			UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
			flags |= D3DCOMPILE_DEBUG;
#endif

			rsl::log::debug("Compiling Shader {}...", file);
			ID3DBlob* errors;
			ID3DBlob* shaderBlob;
			std::string src = source.sources[static_cast<int>(type)].second;
			CHECKERROR(D3DCompile(src.c_str(), src.length(), file.c_str(), nullptr, nullptr, "main", profile.c_str(), flags, 0, &shaderBlob, &errors), "Shader failed to Compile", m_windowHandle->checkError());
		

			if (errors && errors->GetBufferSize())
			{
				rsl::log::error("Shader Compilation {}", errors->GetBufferPointer());
			}
			else
			{
				rsl::log::debug("Shader Compilation Success");
			}


			return std::move(shaderBlob);
		}
	};

	inline bool ShaderCompiler::initialized = false;
	inline window_handle ShaderCompiler::m_windowHandle;
}