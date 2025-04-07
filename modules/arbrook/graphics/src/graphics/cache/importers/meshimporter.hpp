#pragma once
#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <filesystem>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "core/assets/assets.hpp"
#include "graphics/data/mesh.hpp"
#include "graphics/data/materialsource.hpp"

namespace fs = std::filesystem;
namespace rythe::rendering
{
	namespace ast = rythe::core::assets;


	using mesh_parameters = ast::import_settings<mesh>;
	constexpr mesh_parameters default_mesh_params{};


	class MeshImporter : public ast::AssetImporter<mesh>
	{
	private:
		Assimp::Importer m_importer;
		static constexpr aiTextureType types[11] = { aiTextureType_DIFFUSE, aiTextureType_SPECULAR, aiTextureType_NORMALS, aiTextureType_HEIGHT,
			aiTextureType_AMBIENT_OCCLUSION, aiTextureType_EMISSIVE, aiTextureType_METALNESS,
			aiTextureType_DIFFUSE_ROUGHNESS, aiTextureType_CLEARCOAT, aiTextureType_SHEEN, aiTextureType_TRANSMISSION };
	public:
		virtual bool canLoad(fs::path filePath) override;
		virtual ast::asset_handle<mesh> load(rsl::id_type id, fs::path filePath, mesh* data, const ast::import_settings<mesh>& settings) override;
		virtual ast::asset_handle<mesh> loadFromMemory(rsl::id_type id, mesh* data, const ast::import_settings<mesh>& settings) override;
		virtual void write(fs::path filePath, mesh* data) override;
		virtual void free(mesh& asset) override;
	private:
		void initMesh(mesh* data, const aiMesh* _mesh);
		std::vector<material_parameter<std::string>*> initMaterial(const aiScene* scene, aiMaterial* mat, aiTextureType type);

		int getBufferRegisterForType(aiTextureType type)
		{
			static std::unordered_map<aiTextureType, int> typeToRegister = {
				{ aiTextureType_DIFFUSE, 0 },
				{ aiTextureType_SPECULAR, 1 },
				{ aiTextureType_NORMALS, 2 },
				{ aiTextureType_HEIGHT, 3 },
				{ aiTextureType_METALNESS, 4 },
				{ aiTextureType_AMBIENT_OCCLUSION, 5 },
				{ aiTextureType_EMISSIVE, 6 }
			};
			return typeToRegister.contains(type) ? typeToRegister[type] : -1;
		}

		std::string getParameterNameForType(aiTextureType type)
		{
			static std::unordered_map<aiTextureType, std::string> typeToName = {
				{ aiTextureType_DIFFUSE, "Albedo" },
				{ aiTextureType_SPECULAR, "Roughness" },
				{ aiTextureType_NORMALS, "Normals" },
				{ aiTextureType_HEIGHT, "Height" },
				{ aiTextureType_METALNESS, "Metallic" },
				{ aiTextureType_AMBIENT_OCCLUSION, "AmbientOcclusion" },
				{ aiTextureType_EMISSIVE, "Emissive" }
			};
			return typeToName.contains(type) ? typeToName[type] : "Unknown";
		}
	};
}