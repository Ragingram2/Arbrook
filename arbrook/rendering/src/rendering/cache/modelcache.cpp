#include "rendering/cache/modelcache.hpp"

namespace rythe::rendering
{
	std::unordered_map<std::string, std::unique_ptr<model>> ModelCache::m_models;

	model_handle ModelCache::createModel(const std::string& name, const std::string& filePath)
	{
		return  model_handle{};
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