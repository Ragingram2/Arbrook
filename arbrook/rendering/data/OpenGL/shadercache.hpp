#pragma once
#include <string>
#include <sstream>
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
		std::unordered_map<std::string, std::unique_ptr<shader>> m_shaders;
	public:
		shader* loadShader(const std::string& shaderName,const std::string& filepath);
		shader* getShader(const std::string& name);
		void deleteShader(const std::string& shaderName);

	private:
		unsigned int compileShader(unsigned int type, const std::string& source);
		shader_source loadSource(const std::string& filepath);
	};
}