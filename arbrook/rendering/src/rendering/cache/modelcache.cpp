#include "rendering/cache/modelcache.hpp"

namespace rythe::rendering
{
	Assimp::Importer ModelCache::m_importer;

	std::unordered_map<std::string, std::unique_ptr<model>> ModelCache::m_models;

	model_handle ModelCache::createModel(const std::string& name, mesh_handle handle)
	{
		if (m_models.contains(name))
		{
			log::warn("Model {} already exists, ignoring new model, and returning existing one", name);
			return m_models[name].get();
		}
		auto mod = m_models.emplace(name, std::make_unique<model>()).first->second.get();
		mod->initialize(handle);
		return {mod};
	}

	model_handle ModelCache::getModel(const std::string& name)
	{
		if (m_models.contains(name))
		{
			return m_models[name].get();
		}
		log::warn("Model {} does not exist", name);
		return model_handle{};
	}

	void ModelCache::deleteModel(const std::string& name)
	{
		if (m_models.contains(name))
		{
			m_models.erase(name);
		}
	}
}