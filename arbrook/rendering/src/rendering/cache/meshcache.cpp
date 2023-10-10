#include "rendering/cache/meshcache.hpp"

namespace rythe::rendering
{
	Assimp::Importer MeshCache::m_importer;

	std::unordered_map<std::string, std::unique_ptr<mesh>> MeshCache::m_meshes;

	mesh_handle MeshCache::loadMesh(const std::string& name, const std::string& filePath)
	{
		if (m_meshes.contains(name))
		{
			log::warn("Mesh {} already loaded, ignoring new load request, and returning existing one", name);
			return m_meshes[name].get();
		}

		const aiScene* scene = m_importer.ReadFile(filePath, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
		auto mes = m_meshes.emplace(name, std::make_unique<mesh>(scene)).first->second.get();
		return { mes };
	}

	mesh_handle MeshCache::getMesh(const std::string& name)
	{
		if (m_meshes.contains(name))
		{
			return m_meshes[name].get();
		}
		log::warn("Mesh {} does not exist", name);
		return mesh_handle{};
	}

	void MeshCache::deleteMesh(const std::string& name)
	{
		if (m_meshes.contains(name))
		{
			m_meshes.erase(name);
		}
	}
}