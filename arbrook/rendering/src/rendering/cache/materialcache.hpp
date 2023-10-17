#pragma once
#include <string>
#include <memory>
#include <unordered_map>

#include "rendering/data/materialhandle.hpp"
#include "rendering/data/shaderhandle.hpp"
#include "rendering/data/texturehandle.hpp"

namespace rythe::rendering
{
	class MaterialCache
	{
	private:
		static std::unordered_map<std::string, std::unique_ptr<material>> m_materials;
	public:
		//needs import settings
		static material_handle loadMaterial(const std::string& name, const shader_handle shader, const texture_handle texture);
		static material_handle loadMaterialFromFile(const std::string& name, const std::string& shaderPath, const std::string& texturePath);
		static material_handle getMaterial(const std::string& name);
		static void deleteMaterial(const std::string& name);
	};
}