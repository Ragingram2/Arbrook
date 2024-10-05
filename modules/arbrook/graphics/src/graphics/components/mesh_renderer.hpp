#pragma once
#include <unordered_map>

#include <rsl/primitives>
#include <rfl.hpp>
#include <rfl/json.hpp>

#include "core/assets/assethandle.hpp"
#include "core/components/property.hpp"
#include "graphics/data/material.hpp"
#include "graphics/data/model.hpp"



namespace ast = rythe::core::assets;
namespace rythe::rendering
{
	struct mesh_renderer
	{
		bool instanced = false;
		bool castShadows = true;
		rfl::Skip<bool> enabled = true;
		rfl::Skip<bool> dirty = true;
		rfl::Skip<inputlayout> layout;
		std::unordered_map<rsl::id_type, material> materials;
		material mainMaterial;
		model model;
	};
}