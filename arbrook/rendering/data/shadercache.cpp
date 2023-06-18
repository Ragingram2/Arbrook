#include "rendering/data/shadercache.hpp"

namespace rythe::rendering
{
	std::unordered_map<ShaderName, std::unique_ptr<shader>> ShaderCache::m_shaders;
	std::unordered_map<ShaderName, FilePath> ShaderCache::m_filePaths;
	RenderInterface* ShaderCache::m_api;

	shader_handle ShaderCache::createShader(RenderInterface& api, const ShaderName& name, const FilePath& filepath)
	{
		if (m_shaders.contains(name))
		{
			return m_shaders[name].get();
		}
		m_filePaths.emplace(name, filepath);
		auto shad = m_shaders.emplace(name, std::make_unique<shader>()).first->second.get();
		m_api = &api;

		return api.createShader(shad, name, loadShader(filepath));
	}

	shader_handle ShaderCache::getShader(const ShaderName& name)
	{
		if (m_shaders.contains(name))
		{
			return m_shaders[name].get();
		}
		log::warn("Shader {} does not exist", name);
		return shader_handle{};
	}

	void ShaderCache::deleteShader(const std::string& name)
	{
		if (m_shaders.contains(name))
		{
			m_shaders.erase(name);
		}

		if (m_filePaths.contains(name))
		{
			m_filePaths.erase(name);
		}
	}

	void ShaderCache::reloadShaders()
	{
		for (auto& [name, shader] : m_shaders)
		{
			log::debug("reloading {} at path {} ", name, m_filePaths[name]);
			m_api->createShader(shader.get(), name, loadShader(m_filePaths[name]));
		}
		log::debug("Done!");
	}

	shader_source ShaderCache::loadShader(const std::string& filepath)
	{
		std::ifstream stream(filepath);

		enum class ShaderType
		{
			NONE = -1,
			VERTEX = 0,
			FRAG = 1
		};

		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;
		bool parse = false;
		auto langDefine = std::string("#").append(ShaderLanguage);

		while (getline(stream, line))
		{
			if (line.find(langDefine) != std::string::npos)
			{
				parse = true;
				continue;
			}
			else if (parse && line.find("#END") != std::string::npos)
			{
				parse = false;
				break;
			}

			if (parse)
			{
				if (line.find("#shader") != std::string::npos)
				{
					if (line.find("vertex") != std::string::npos)
					{
						type = ShaderType::VERTEX;
					}
					else if (line.find("fragment") != std::string::npos)
					{
						type = ShaderType::FRAG;
					}
				}
				else
				{
					ss[(int)type] << line << "\n";
				}
			}
		}

		return { ss };
	}

}