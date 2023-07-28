#include "rendering/data/handles/modelhandle.hpp"
#include "rendering/cache/cache.hpp"

namespace rythe::rendering
{
	model_handle::model_handle(const std::string& name)
	{
		model = ModelCache::getModel(name).model;
	}

	model_handle::model_handle(struct model* _model)
	{
		model = _model;
	}
}