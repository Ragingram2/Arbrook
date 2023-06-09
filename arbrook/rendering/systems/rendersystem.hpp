#pragma once
#include <chrono>
#include <ctime>
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


	struct result_times
	{
		float setupTime;
		float frameTime;
	};

	struct test_result
	{
		std::unordered_map<APIType, result_times> testTimes;

		void printResult()
		{
			for (auto& [type, resultTime] : testTimes)
			{
				std::string api;
				switch (type)
				{
				case APIType::Arbrook:
					api = "Arbrook";
					break;
				case APIType::BGFX:
					api = "BGFX";
					break;
				case APIType::Native:
					api = "Native";
					break;
				case APIType::None:
					api = "None";
					break;
				}
				log::debug("API[{}]: Test took {} ms to initialize", api, resultTime.setupTime);
				log::debug("API[{}]: Test took an average of {} ms per frame", api, resultTime.frameTime);
			}
		}
	};

	struct CSVWriter
	{
		std::unordered_map<std::string, test_result> results;

		void writeSetupTime(std::string testName, APIType type, float setupTime)
		{
			log::debug(testName);
			results[testName].testTimes[type].setupTime = setupTime;
		}

		void writeFrameTime(std::string testName, APIType type, float frameTime)
		{
			results[testName].testTimes[type].frameTime = frameTime;
		}

		void printResults()
		{
			for (auto& [name, result] : results)
			{
				log::debug("Results for test \"{}\"", name);
				result.printResult();
			}

			results.clear();
		}
	};

	class Renderer : public core::System<core::transform, sprite_renderer, core::exampleComp>
	{
	public:
		RenderInterface* m_api;
		static float count;

		static std::vector<std::unique_ptr<rendering_test>> m_testScenes;
		static int currentScene;
		static int lastScene;

		static bool initializeTest;
		static bool updateTest;
		static bool stopTest;

		CSVWriter writer;
		int testCount = 0;
		float maxTests = 100.0f;
		float timeSum = 0.0f;

		Renderer() = default;
		virtual ~Renderer() = default;

		void setup() override;
		void update() override;
		void shutdown() override;

		void TestStencilTest();

		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (action == GLFW_PRESS)
			{
				lastScene = currentScene;
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

			if (currentScene > static_cast<int>(m_testScenes.size() - 1))
			{
				currentScene = 0;
			}
			else if (currentScene < 0)
			{
				currentScene = m_testScenes.size() - 1;
			}
		}
	};
}