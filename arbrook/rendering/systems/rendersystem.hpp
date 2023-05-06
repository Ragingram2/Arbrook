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
		static float count;

		static std::vector<void(Renderer::*)()> m_testScenes;
		static int currentScene;

		Renderer() = default;
		virtual ~Renderer() = default;

		void setup() override;
		void update() override;
		void shutdown() override;

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

		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (action == GLFW_PRESS)
			{
				switch (key)
				{
				case GLFW_KEY_RIGHT:
					currentScene++;
					break;
				case GLFW_KEY_LEFT:
					currentScene--;
					break;
				}
			}

			if (currentScene >= m_testScenes.size())
				currentScene = 0;
			else if (currentScene <= 0)
				currentScene = m_testScenes.size() - 1;

			count = 0;

		}
	};
}