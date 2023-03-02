#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <unordered_map>

#include <GL/glew.h>

#include "core/core.hpp"
#include "rendering/data/shader.hpp"
#include "rendering/data/shadersource.hpp"
#include "rendering/data/shaderhandle.hpp"
#include "rendering/data/definitions.hpp"

namespace rythe::rendering
{
	class ShaderCache
	{
	private:
		static RenderInterface m_api;
		static std::unordered_map<std::string, std::unique_ptr<shader>> m_shaders;

	public:
		static shader_handle createShader(const std::string& name,const std::string& filepath);
		static shader_handle getShader(const std::string& name);
		static void deleteShader(const std::string& name);
	};
}