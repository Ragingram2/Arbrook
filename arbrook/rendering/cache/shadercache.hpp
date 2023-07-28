#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <unordered_map>

#include "core/core.hpp"
#include "rendering/data/shadersource.hpp"
#include "rendering/data/shaderhandle.hpp"
#include "rendering/interface/definitions.hpp"

namespace rythe::rendering
{
	typedef std::string ShaderName;
	typedef std::string FilePath;

	class ShaderCache
	{
	private:
		static std::unordered_map<std::string, std::unique_ptr<shader>> m_shaders;
		static std::unordered_map<ShaderName, FilePath> m_filePaths;
		static RenderInterface* m_api;
	public:
		static shader_handle createShader(RenderInterface& api, const ShaderName& name,const FilePath& filepath);
		static shader_handle getShader(const std::string& name);
		static void deleteShader(const std::string& name);
		static void reloadShaders();
		static shader_source loadShader(const std::string& filepath);
	};
}