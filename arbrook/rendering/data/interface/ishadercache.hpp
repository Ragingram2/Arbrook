#pragma once
#include <string>
#include <sstream>
#include <memory>
#include <unordered_map>

#include "core/core.hpp"
#include "rendering/data/interface/shader.hpp"
#include <rendering/data/interface/shadersource.hpp>

namespace rythe::rendering
{
	template<typename APIType>
	class IShaderCache
	{
	private:
		APIType m_impl;
	public:
		shader* loadShader(const std::string& shaderName, const std::string& filepath) { return *m_impl.loadShader(shaderName, filepath); }
		shader* getShader(const std::string& name) { return *m_impl.getShader(name); }
		void deleteShader(const std::string& shaderName) { m_impl.deleteShader(shaderName); }

	private:
		unsigned int compileShader(unsigned int type, const std::string& source) { return m_impl.compileShader(type, source); }
		shader_source loadSource(const std::string& filepath) { return m_impl.loadSource(filepath); }
	};
}