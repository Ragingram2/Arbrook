#pragma once
#include <rsl/math>
#include <rfl.hpp>
#include <rfl/json.hpp>
#include <rfl/Variant.hpp>
#include "core/utils/profiler.hpp"
#include "core/components/transform.hpp"
#include "core/ecs/component_family.hpp"
#include "graphics/interface/definitions/definitions.hpp"

namespace rythe::rendering
{
	struct camera_data
	{
		math::vec3 viewPosition;
		math::mat4 projection;
		math::mat4 view;
		math::mat4 model;
	};

	struct camera
	{
	public:
		rfl::Skip<bool> enabled = true;
		rfl::Skip<framebuffer> renderTarget;
		math::mat4 projection;
		math::mat4 view;
		float nearZ = 1.0f;
		float farZ = 100.f;
		float fov = 60;
	};
}