#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "core/systems/system.hpp"
#include "core/logging/logging.hpp"
#include "rendering/data/buffer.hpp"
#include "rendering/components/shaperenderer.hpp"

namespace rythe::core
{
	namespace gfx = rythe::rendering;
	class TestSystem : public System<transform, gfx::shape_renderer>
	{
	public:
		TestSystem() = default;
		virtual ~TestSystem() = default;

		void setup() override;
		void update() override;
		void shutdown() override;
	};
}