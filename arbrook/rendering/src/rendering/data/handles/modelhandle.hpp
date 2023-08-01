#pragma once
#include "rendering/data/model.hpp"

namespace rythe::rendering
{
	struct model_handle
	{
		model* model = nullptr;
		model_handle() = default;
		model_handle(const std::string& name);
		model_handle(struct model* _model);

		struct model* operator->() { return model; }
		operator struct model& () const { return *model; }
	};
}