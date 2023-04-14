#include "rendering/data/shadercache.hpp"

namespace rythe::rendering
{
	std::unordered_map<std::string, std::unique_ptr<shader>> ShaderCache::m_shaders;

	shader_handle ShaderCache::createShader(RenderInterface& api, const std::string& name, const std::string& filepath)
	{
		if (m_shaders.contains(name))
		{
			log::warn("Shader {} already exists, ignoring new shader, and returning existing one", name);
			return m_shaders[name].get();
		}

		auto shad = m_shaders.emplace(name, std::make_unique<shader>()).first->second.get();

		return api.createShader(shad, name, loadShader(filepath));
	}

	shader_handle ShaderCache::getShader(const std::string& name)
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