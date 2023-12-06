#pragma once
#include <filesystem>

#include <d3d12shader.h>
#include <DxErr.h>
#include <dxcerrors.h>
#include <dxcapi.h>
#include <winerror.h>
#pragma comment(lib, "dxcompiler.lib")

#include <rsl/logging>
#include <rsl/primitives>

#include "rendering/interface/config.hpp"
#include "rendering/data/shadersource.hpp"
#include "rendering/cache/windowprovider.hpp"


namespace rythe::rendering::internal
{
	class ShaderCompiler
	{
	private:
		//static IDxcCompiler2* m_compiler;
		static IDxcCompiler3* m_compiler;
		static IDxcUtils* m_utils;
		static IDxcIncludeHandler* m_include_handler;
		static bool initialized;
		static window_handle m_windowHandle;
	public:
		static void initialize()
		{
			if (initialized) return;
			m_windowHandle = WindowProvider::get(0);

			CHECKERROR(DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&m_compiler)), "Failed to create a DX Compiler instance", m_windowHandle->checkError());
			CHECKERROR(DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&m_utils)), "Failed to create a DX Utils instance", m_windowHandle->checkError());
			CHECKERROR(m_utils->CreateDefaultIncludeHandler(&m_include_handler), "Failed to create a DX IncludeHandler", m_windowHandle->checkError());
			initialized = true;
		}

		static unsigned int compile(ShaderType type, shader_source source)
		{
			std::string profile;
			int shaderIdx = 0;
			switch (static_cast<ShaderType>(type))
			{
			case ShaderType::VERTEX:
				profile = "vs_6_0";
				shaderIdx = 0;
				break;
			case ShaderType::FRAGMENT:
				profile = "ps_6_0";
				shaderIdx = 1;
				break;
			case ShaderType::GEOMETRY:
				profile = "gs_6_0";
				shaderIdx = 2;
				break;
			case ShaderType::HULL:
				profile = "hs_6_0"; 
				shaderIdx = 3;
				break;
			case ShaderType::COMPUTE:
				profile = "cs_6_0";
				shaderIdx = 4;
				break;
			}

			IDxcBlob* spirVBin = compileToSpirV(profile, source.fileName, source.sources[shaderIdx].second);

			log::debug("SpirV Binary: {}", spirVBin->GetBufferPointer());

			unsigned int id = glCreateShader(static_cast<GLenum>(type));
			std::string file{ std::format("{}-{}", source.fileName, profile) };
			rsl::log::debug("Compiling SpirV Shader {}...", file);
			glShaderBinary(1, &id, GL_SHADER_BINARY_FORMAT_SPIR_V_ARB, spirVBin->GetBufferPointer(), spirVBin->GetBufferSize());
			glSpecializeShader(id, "main", 0u, nullptr, nullptr);

			GLint isCompiled = 0;
			glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(id, maxLength, &maxLength, &infoLog[0]);
				rsl::log::error("Shader Compilation Failed");
				rsl::log::error("Shader Compilation {}", infoLog.data());

				glDeleteShader(id);
				return 0;
			}

			rsl::log::debug("SpirV Shader Compilation Success");

			return id;
		}

	private:
		static IDxcBlob* compileToSpirV(const std::string& profile, const std::string& fileName, const std::string& source)
		{
			log::debug("Shader Source: {}", source);
			IDxcBlobEncoding* srcBlob;
			CHECKERROR(m_utils->CreateBlob(source.c_str(), source.size(), CP_UTF8, &srcBlob), "Failed to create a blob from shader source", m_windowHandle->checkError());

			std::wstring wprofile = rsl::to_wstring(profile);
			std::string file{ std::format("{}-{}", fileName, profile) };
			std::wstring wfile{ rsl::to_wstring(file) };

			LPCWSTR args[]
			{
				L"-spirv",
				wfile.c_str(),
				L"-E ", L"main",
				L"-T ", wprofile.c_str(),
				L"-HV", L"2021",
				L"-flegacy-resource-reservation",
				L"-flegacy-macro-expansion",
				L"-Wconversion",
				DXC_ARG_ALL_RESOURCES_BOUND,
#if _DEBUG
				DXC_ARG_DEBUG,
				DXC_ARG_SKIP_OPTIMIZATIONS,
#else
				DXC_ARG_OPTIMIZATIONS_LEVEL3,
#endif
				L"-Qstrip_reflect",
				L"-Qstrip_debug"
			};

			rsl::log::debug("Compiling Shader {} to SpirV", file);

			DxcBuffer _buffer{};
			_buffer.Encoding = DXC_CP_ACP;
			_buffer.Ptr = srcBlob->GetBufferPointer();
			_buffer.Size = srcBlob->GetBufferSize();

			IDxcResult* results{ nullptr };
			CHECKERROR(m_compiler->Compile(&_buffer, args, _countof(args), m_include_handler, IID_PPV_ARGS(&results)), std::format("Failed to compile shader {}", file), m_windowHandle->checkError());

			IDxcBlobUtf8* errors{ nullptr };
			CHECKERROR(results->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&errors), nullptr),"Getting Errors failed",m_windowHandle->checkError());

			if (errors && errors->GetStringLength())
			{
				rsl::log::error("Shader SpirV Compilation {}", errors->GetStringPointer());
			}
			else
			{
				rsl::log::debug("Shader SpirV Compilation Success");
			}

			IDxcBlob* _shader{ nullptr };
			CHECKERROR(results->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&_shader), nullptr),"Getting shader blob failed",m_windowHandle->checkError());
			return std::move(_shader);
		}
	};

	inline IDxcCompiler3* ShaderCompiler::m_compiler;
	inline IDxcUtils* ShaderCompiler::m_utils;
	inline IDxcIncludeHandler* ShaderCompiler::m_include_handler;
	inline bool ShaderCompiler::initialized = false;
	inline window_handle ShaderCompiler::m_windowHandle;
}