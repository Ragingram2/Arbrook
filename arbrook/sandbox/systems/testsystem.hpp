#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "core/systems/system.hpp"
#include "core/logging/logging.hpp"
#include "rendering/data/buffer.hpp"
#include "rendering/components/spriterenderer.hpp"
#include "rendering/data/window.hpp"

namespace rythe::core
{
	namespace gfx = rythe::rendering;
	class TestSystem : public System<transform>
	{
	public:
		float count = 0.0f;
		TestSystem() = default;
		virtual ~TestSystem() = default;

		void setup() override;
		void update() override;
		void shutdown() override;
	};
}