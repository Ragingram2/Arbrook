#include "rendering/data/shadercache.hpp"

namespace rythe::rendering
{
	std::unordered_map<std::string, std::unique_ptr<shader>> ShaderCache::m_shaders;
	RenderInterface ShaderCache::m_api;

	shader_handle ShaderCache::createShader(const std::string& name, const std::string& filepath)
	{
		if (m_shaders.contains(name))
		{
			log::warn("Shader {} already exists, ignoring new shader, and returning existing one", name);
			return m_shaders[name].get();
		}

		auto& shad = m_shaders.emplace(name, std::make_unique<shader>()).first->second;

		return m_api.createShader(shad.get(), name, filepath);
	}

	shader_handle ShaderCache::getShader(const std::string& name)
	{
		if (m_shaders.contains(name))
		{
			return m_shaders[name].get();
		}
		log::warn("Shader {} does not exist", name);
		return nullptr;
	}

	void ShaderCache::deleteShader(const std::string& name)
	{

	}

}