#pragma once
#include <memory>

#include "core/core.hpp"
#include "core/events/defaults/exit_event.hpp"
#include "rendering/data/definitions.hpp"
#include "rendering/data/shadercache.hpp"
#include "rendering/data/texturecache.hpp"
#include "rendering/data/buffercache.hpp"
#include "rendering/components/spriterenderer.hpp"
#include "rendering/data/vertex.hpp"

namespace rythe::rendering
{
	namespace log = core::log;
	namespace math = core::math;

	class Renderer : public core::System<core::transform, sprite_renderer, core::exampleComp>
	{
	public:
		RenderInterface* m_api;
		core::ecs::entity testEnt;
		float count = 0;

		Renderer() = default;
		virtual ~Renderer() = default;

		void setup() override;
		void update() override;
		void shutdown() override;

		//void TestClearColor();
		//void TestClearDepth();
		//void TestClearStencil();
		void TestDrawArrays();
		void TestDrawArraysInstanced();
		void TestDrawIndexed();
		void TestDrawIndexedInstanced();
		void TestSetViewport();
		void TestDepthTest();
		void TestStencilTest();

		void TestCreateShader();
		void TestCreateTexture();
		void TestCreateBuffer();
	};
}