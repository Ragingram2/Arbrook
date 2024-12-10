#include "graphics/cache/shadercache.hpp"

namespace rythe::rendering
{
	std::unordered_map<rsl::id_type, std::unique_ptr<shader>> ShaderCache::m_shaders;
	std::unordered_map<rsl::id_type, std::string> ShaderCache::m_names;

	shader_handle ShaderCache::createShader(const std::string& name, ast::asset_handle<shader_source> shaderSource)
	{
		rsl::id_type id = rsl::hash_string(name);
		if (m_shaders.count(id))
		{
			log::warn("This shader name \"{}\" already exists, returning existing handle", name);
			return { m_shaders[id].get() };
		}

		auto shad = m_shaders.emplace(id, std::make_unique<shader>()).first->second.get();
		shad->m_impl.initialize(name, shaderSource);
		m_names.emplace(id, name);
		return { shad };
	}

	void ShaderCache::createShaders(std::vector<ast::asset_handle<shader_source>> assets)
	{
		for (auto& source : assets)
		{
			createShader(source->name, source);
		}
	}

	void ShaderCache::compileShaders(bool async)
	{
		(void)async;
		log::info("Compiling all shaders");
		for (auto& [id, shad] : m_shaders)
		{
			auto source = ast::AssetCache<shader_source>::getAsset(m_names[id]);
			shad->m_impl.initialize(m_names[id], source);
		}
		log::info("Finished compiling all shaders");
	}

	shader_handle ShaderCache::getShader(const std::string& name)
	{
		return getShader(rsl::hash_string(name));
	}

	shader_handle ShaderCache::getShader(rsl::id_type hash_string)
	{
		if (m_shaders.count(hash_string))
		{
			return { m_shaders[hash_string].get() };
		}
		log::error("Shader id \"{}\" does not exist", hash_string);
		return { nullptr };
	}

	void ShaderCache::deleteShader(const std::string& name)
	{
		deleteShader(rsl::hash_string(name));
	}

	void ShaderCache::deleteShader(rsl::id_type hash_string)
	{
		if (m_shaders.count(hash_string))
		{
			m_shaders[hash_string]->release();
			m_shaders.erase(hash_string);
			m_names.erase(hash_string);
		}
	}

	void ShaderCache::deleteShaders()
	{
		for (auto& [id, handle] : m_shaders)
		{
			deleteShader(id);
		}
	}

	std::vector<shader_handle> ShaderCache::getShaders()
	{
		std::vector<shader_handle> handles;
		for (auto& [id, handle] : m_shaders)
		{
			handles.emplace_back(handle.get());
		}
		return handles;
	}

	std::vector<std::string> ShaderCache::getShaderNames()
	{
		std::vector<std::string> names;
		for (auto& [id, name] : m_names)
		{
			names.push_back(name);
		}
		return names;
	}

	std::vector<const char*> ShaderCache::getShaderNamesC()
	{
		std::vector<const char*> names;
		for (auto& [id, name] : m_names)
		{
			names.push_back(name.c_str());
		}
		return names;
	}

}