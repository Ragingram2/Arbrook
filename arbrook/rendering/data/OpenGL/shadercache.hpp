#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <memory>
#include <unordered_map>

#include <GL/glew.h>

#include "core/core.hpp"
#include "rendering/data/interface/shader.hpp"
#include <rendering/data/interface/shadersource.hpp>

namespace rythe::rendering::internal
{
	class ShaderCache
	{
	private:
		static std::unordered_map<std::string, std::unique_ptr<shader>> m_shaders;
	public:
		static shader* loadShader(const std::string& name,const std::string& filepath);
		static shader* getShader(const std::string& name);
		static void deleteShader(const std::string& name);

	private:
		static unsigned int compileShader(unsigned int type, const std::string& source);
		static shader_source loadSource(const std::string& filepath);
	};
}