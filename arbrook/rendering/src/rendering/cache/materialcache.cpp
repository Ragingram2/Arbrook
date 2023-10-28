#include "rendering/cache/materialcache.hpp"
#include "rendering/cache/shadercache.hpp"
#include "rendering/cache/texturecache.hpp"

namespace rythe::rendering
{
	std::unordered_map<std::string, std::unique_ptr<material>> MaterialCache::m_materials;

	material_handle MaterialCache::loadMaterial(const std::string& name, const shader_handle shader, const texture_handle texture)
	{
		if (m_materials.contains(name))
		{
			log::warn("Material {} already exists, ignoring creation request and returning existing material", name);
			return { m_materials[name].get() };
		}

		auto mat = m_materials.emplace(name, std::make_unique<material>()).first->second.get();
		mat->shader = shader;
		mat->texture = texture;
		return { mat };
	}
	material_handle MaterialCache::loadMaterial(const std::string& name, const std::string& shaderName)
	{
		return loadMaterial(name, ShaderCache::getShader(shaderName), texture_handle{});
	}
	material_handle MaterialCache::loadMaterial(const std::string& name, const std::string& shaderName, const std::string& textureName)
	{
		return loadMaterial(name, ShaderCache::getShader(shaderName), TextureCache::getTexture2D(textureName));
	}
	material_handle MaterialCache::loadMaterialFromFile(const std::string& name, const std::string& shaderPath, const std::string& texturePath)
	{
		shader_handle shader = ShaderCache::createShader(std::format("{}_shader", name), shaderPath);
		texture_handle texture = TextureCache::createTexture2D(std::format("{}_texture", name), texturePath);

		return loadMaterial(name, shader, texture);
	}
	material_handle MaterialCache::getMaterial(const std::string& name)
	{
		if (m_materials.contains(name))
		{
			return { m_materials[name].get() };
		}
		return material_handle();
	}
	void MaterialCache::deleteMaterial(const std::string& name)
	{
		if (m_materials.contains(name))
		{
			m_materials[name]->shader->clearBuffers();
			//add a similar func for textures
			m_materials.erase(name);
		}
	}
}