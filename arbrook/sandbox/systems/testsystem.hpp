#pragma once
#include <GL/glew.h>

#include "core/core.hpp"
#include "rendering/rendering.hpp"

namespace rythe::core
{
	class TestSystem : public System<transform>
	{
	public:
		gfx::RenderInterface m_renderAPI;
		TestSystem() = default;
		virtual ~TestSystem() = default;

		void setup() override;
		void update() override;
		void shutdown() override;
	};
}