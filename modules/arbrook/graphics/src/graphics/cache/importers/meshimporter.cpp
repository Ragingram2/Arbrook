#include "graphics/cache/importers/meshimporter.hpp"
#include "graphics/cache/materialcache.hpp"
#include "graphics/data/materialsource.hpp"
#include "graphics/cache/texturecache.hpp"

#include <stb/stb_image.h>

namespace fs = std::filesystem;
namespace ast = rythe::core::assets;

template<>
std::unordered_map<rsl::id_type, std::unique_ptr<ast::AssetImporter<rythe::rendering::mesh>>> ast::AssetCache<rythe::rendering::mesh>::m_importers;
template<>
std::unordered_map<rsl::id_type, std::unique_ptr<rythe::rendering::mesh>> ast::AssetCache<rythe::rendering::mesh>::m_assets;
template<>
std::unordered_map<rsl::id_type, std::string> ast::AssetCache<rythe::rendering::mesh>::m_names;

namespace rythe::rendering
{
	bool MeshImporter::canLoad(fs::path filePath)
	{
		return m_importer.IsExtensionSupported(filePath.extension().string().c_str());
	}

	ast::asset_handle<mesh> MeshImporter::load(rsl::id_type id, fs::path filePath, mesh* data, const ast::import_settings<mesh>& settings)
	{
		(void)settings;
		const aiScene* scene = m_importer.ReadFile(filePath.string(), /*aiProcess_GenSmoothNormals |*/ aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType | aiProcess_FlipWindingOrder | aiProcess_PreTransformVertices);
		if (!scene)
		{
			log::error("Problem in loading mesh file");
			return { 0, nullptr };
		}
		data->name = filePath.stem().string();

		if (!scene->HasMeshes())
		{
			log::error("The scene we tried to load did not contain any meshes, curious");
			return{ 0, nullptr };
		}

		data->meshes.reserve(scene->mNumMeshes);
		data->vertexCount = 0;
		data->indexCount = 0;

		for (unsigned int i = 0; i < scene->mNumMeshes; i++)
		{
			data->meshes.emplace_back();
			data->meshes[i].materialIdx = scene->mMeshes[i]->mMaterialIndex;
			data->meshes[i].name = scene->mMeshes[i]->mName.C_Str();
			data->meshes[i].count = scene->mMeshes[i]->mNumFaces * 3;
			data->meshes[i].vertexOffset = data->vertexCount;
			data->meshes[i].indexOffset = data->indexCount;

			data->vertexCount += scene->mMeshes[i]->mNumVertices;
			data->indexCount += data->meshes[i].count;

			if (scene->mNumMaterials < 1) continue;

			aiMaterial* material = scene->mMaterials[scene->mMeshes[i]->mMaterialIndex];
			auto matAssets = ast::AssetCache<material_source>::getAssets();
			auto matName = i == 0 ? std::format("{}-material", data->name) : std::format("{}{}-material", data->name, i);
			auto filePath = "resources/shaders/lit.shader";
			auto shaderName = "lit";
			auto mat_source = material_source{ .name = matName,  .shaderName = shaderName, .shaderPath = filePath };
			for (aiTextureType type : types)
			{
				auto textures = initMaterial(scene, material, type);
				for (auto texture : textures)
				{
					texture->bufferRegister = getBufferRegisterForType(type);
					texture->type = ParamType::Texture;
					mat_source.parameters.emplace(getParameterNameForType(type), texture);
				}
			}

			auto matAsset = ast::AssetCache<material_source>::createAssetFromMemory(matName, mat_source, ast::import_settings<material_source>{});
			auto matHandle = MaterialCache::loadMaterial(matName, matAsset);
			matHandle->data = material_data
			{
				.diffuseColor = math::vec4(1.0,1.0,1.0,1.0),
				.hasAlbedo =1,
				.hasRoughness = 1,
				.hasRoughnessMetallic = 1,
				.hasNormal = 1,
				.hasHeight =1,
				.hasMetallic =1,
				.hasAmbientOcclusion = 1,
				.hasEmissive =1,

			};
			matAssets = ast::AssetCache<material_source>::getAssets();
			data->materialIds[data->meshes[i].materialIdx] = matHandle.m_id;
		}

		for (unsigned int i = 0; i < data->meshes.size(); i++)
		{
			initMesh(data, scene->mMeshes[i]);
		}

		return { id, data };
	}

	ast::asset_handle<mesh> MeshImporter::loadFromMemory(rsl::id_type id, mesh* data, const ast::import_settings<mesh>& settings)
	{
		(void)settings;
		return { id, data };
	}

	void MeshImporter::write(fs::path filePath, mesh* data)
	{
		(void)filePath;
		(void)data;
		//std::ofstream o(filePath);
		//nlohmann::json j;
		//ns::to_json(j, *data);
		//o << std::setw(4) << j << std::endl;
	}

	void MeshImporter::free(mesh&) {}

	void MeshImporter::initMesh(mesh* data, const aiMesh* _mesh)
	{
		const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
		auto count = _mesh->mNumVertices;

		for (unsigned int i = 0u; i < count; i++)
		{
			const aiVector3D& vertex = _mesh->mVertices[i];
			const aiVector3D& normal = _mesh->mNormals[i];
			const aiVector3D& tangent = _mesh->HasTangentsAndBitangents() ? _mesh->mTangents[i] : Zero3D;
			const aiVector3D texcoord = _mesh->HasTextureCoords(0) ? _mesh->mTextureCoords[0][i] : Zero3D;

			data->vertices.push_back(math::vec4(vertex.x, vertex.y, vertex.z, 1.0f));
			data->normals.push_back(math::vec3(normal.x, normal.y, normal.z));
			data->texCoords.push_back(math::vec2(texcoord.x, texcoord.y));
			data->tangents.push_back(math::vec3(tangent.x, tangent.y, tangent.z));
		}

		if (_mesh->HasVertexColors(0))
		{
			auto s_colors = _mesh->mColors[0];

			for (unsigned int i = 0u; i < count; i++)
			{
				data->colors.push_back(math::vec4(s_colors[i].r, s_colors[i].g, s_colors[i].b, s_colors[i].a));
			}
		}

		if (_mesh->HasFaces())
			for (unsigned int i = 0u; i < _mesh->mNumFaces; i++)
			{
				auto indexCount = _mesh->mFaces[i].mNumIndices;
				auto s_indices = _mesh->mFaces[i].mIndices;
				for (unsigned int j = 0u; j < indexCount; j++)
				{
					data->indices.push_back(s_indices[j]);
				}
			}
	}
	std::vector<material_parameter<std::string>*> MeshImporter::initMaterial(const aiScene* scene, aiMaterial* mat, aiTextureType type)
	{
		std::vector<material_parameter<std::string>*> textures;
		auto texCount = mat->GetTextureCount(type);

		for (unsigned int j = 0; j < texCount; j++)
		{
			aiString strPath;
			mat->GetTexture(type, j, &strPath);

			if (strPath.length == 0) continue;

			if (strPath.data[0] == '*') // Embedded texture
			{
				int idx = atoi(strPath.data + 1);
				if (idx >= scene->mNumTextures)
				{
					log::error("Invalid embedded texture index: {}", idx);
					continue;
				}

				aiTexture* texture = scene->mTextures[idx];
				std::string textureName = std::format("{}-{}", mat->GetName().C_Str(), texture->mFilename.C_Str());
				math::uvec2 resolution = { 0, 0 };
				int channels = 0;
				unsigned char* textureData = nullptr;

				if (texture->mHeight == 0) 
				{
					textureData = stbi_load_from_memory(
						reinterpret_cast<unsigned char*>(texture->pcData), texture->mWidth,
						&resolution.x, &resolution.y, &channels, 0);
				}
				else
				{
					resolution = { texture->mWidth, texture->mHeight };
					channels = 4; // Assimp stores uncompressed textures in 4-channel format
					textureData = new unsigned char[resolution.x * resolution.y * channels];
					memcpy(textureData, texture->pcData, resolution.x * resolution.y * channels);
				}

				if (textureData)
				{
					auto tex_source = texture_source{
						.name = textureName,
						.data = textureData,
						.resolution = resolution,
						.channels = channels
					};

					auto textureAsset = ast::AssetCache<texture_source>::createAssetFromMemory(textureName, tex_source, ast::import_settings<texture_source>{});
					auto texHandle = TextureCache::createTexture2D(textureName, textureAsset);
					textures.emplace_back(new material_parameter<std::string>{ .value = texHandle->getName() });

					stbi_image_free(textureData);
				}
			}
			else // External texture file
			{
				std::string fullPath = strPath.C_Str();
				if (!fs::exists(fullPath))
				{
					log::warn("Texture file not found: {}", fullPath);
					continue;
				}

				auto textureAsset = ast::AssetCache<texture_source>::createAsset(strPath.C_Str(), fs::path(fullPath), ast::import_settings<texture_source>{});
				auto texHandle = TextureCache::createTexture2D(strPath.C_Str(), textureAsset);
				textures.emplace_back(new material_parameter<std::string>{ .value = texHandle->getName() });
			}
		}
		return textures;
	}
}