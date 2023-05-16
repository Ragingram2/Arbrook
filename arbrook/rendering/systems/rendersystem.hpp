#pragma once
#include <memory>

#include "core/core.hpp"
#include "core/events/defaults/exit_event.hpp"
#include "rendering/data/definitions.hpp"
#include "rendering/data/shadercache.hpp"
#include "rendering/data/texturecache.hpp"
#include "rendering/data/buffercache.hpp"
#include "rendering/components/spriterenderer.hpp"
#include "rendering/data/renderingtest.hpp"
#include "rendering/data/vertex.hpp"

namespace rythe::rendering
{
	namespace log = core::log;
	namespace math = core::math;

	static math::vec3* generateVertexData(math::vec3 position = math::vec3(0, 0, 0), math::vec3 dimensions = math::vec3(.1f, .1f, 0.0f))
	{
		math::vec3 data[6] =
		{
			{(math::vec3(-1.0f,1.0f,0.0f) * dimensions) + position},
			{(math::vec3(-1.0f,-1.0f,0.0f) * dimensions) + position},
			{(math::vec3(1.0f,-1.0f,0.0f) * dimensions) + position},
			{(math::vec3(-1.0f,1.0f,0.0f) * dimensions) + position},
			{(math::vec3(1.0f,-1.0f,0.0f) * dimensions) + position},
			{(math::vec3(1.0f,1.0f,0.0f) * dimensions) + position}
		};
		return std::move(data);
	}

	class Renderer : public core::System<core::transform, sprite_renderer, core::exampleComp>
	{
	public:
		RenderInterface* m_api;
		static float count;

		static std::vector<rendering_test> m_testScenes;
		static int currentScene;

		static bool initializeTest;
		static bool updateTest;
		static bool stopTest;

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
					stopTest = true;
					updateTest = false;
					initializeTest = true;
					break;
				case GLFW_KEY_LEFT:
					currentScene--;
					stopTest = true;
					updateTest = false;
					initializeTest = true;
					break;
				}
			}

			if (currentScene > m_testScenes.size() - 1)
				currentScene = 0;
			else if (currentScene < 0)
				currentScene = m_testScenes.size() - 1;

		}
	};
}