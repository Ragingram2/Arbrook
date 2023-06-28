#pragma once
#include <chrono>
#include <ctime>
#include <memory>
#include <iostream>
#include <filesystem>

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

	struct result_times
	{
		std::int64_t setupTime;
		std::vector<std::int64_t> frameTimes;
		std::int64_t numObjects;
	};

	struct test_result
	{
		std::unordered_map<APIType, result_times> testTimes;

		std::string serialize()
		{
			std::string times;

			for (auto& [t, resultTime] : testTimes)
			{
				if (t == APIType::None)
					continue;

				times.append(std::format("{},Setup,NumObjects,", stringify(t)));
			}

			size_t max = 0;
			times.append("\n");

			for (auto& [t, resultTime] : testTimes)
			{
				if (resultTime.frameTimes.size() >= max)
				{
					max = resultTime.frameTimes.size();
				}
			}
			for (size_t i = 0; i < max; i++)
			{

				for (auto& [t, resultTime] : testTimes)
				{
					if (t == APIType::None)
						continue;

					if (i < resultTime.frameTimes.size())
					{
						times.append(std::format("{},", resultTime.frameTimes[i]));
					}
					else
					{
						times.append(" ,");
					}

					if (i == 0)
					{
						times.append(std::format("{},{},", resultTime.setupTime, resultTime.numObjects));
					}
					else
					{
						times.append(" , ,");
					}
				}
				times.append("\n");
			}

			return times;
		}

		void printResult()
		{
			//			for (auto& [type, resultTime] : testTimes)
			//			{
			//				std::string api;
			//				switch (type)
			//				{
			//				case APIType::Arbrook:
			//					api = "Arbrook";
			//					break;
			//				case APIType::BGFX:
			//					api = "BGFX";
			//					break;
			//				case APIType::Native:
			//#if RenderingAPI == RenderingAPI_OGL
			//					api = "NativeOGL";
			//#elif RenderingAPI == RenderingAPI_DX11
			//					api = "NativeDX11";
			//#endif
			//					break;
			//				case APIType::None:
			//					api = "None";
			//					break;
			//				}
			//				log::debug("API[{}]: Test took {} ms to initialize", api, resultTime.setupTime);
			//				log::debug("API[{}]: Test took an average of {} ms per frame", api, resultTime.frameTime);
			//
						//}
		}
	};

	struct CSVWriter
	{
	private:
		std::string fullPath;
		std::string filePath;
		std::string fileName;

		std::string output;
	public:
		std::unordered_map<std::string, test_result> results;

		CSVWriter(std::string path)
		{
			fullPath = path;
			auto idx = path.find_last_of('/');
			fileName = path.substr(idx+1, path.size() - 1);
			filePath = path.substr(0, idx);
		}

		void writeSetupTime(std::string testName, APIType type, std::int64_t setupTime)
		{
			if (type == None)
				return;
			results[testName].testTimes[type].setupTime = setupTime;
		}

		void writeNumObjects(std::string testName, APIType type, std::int64_t numObjects)
		{
			if (type == None)
				return;
			results[testName].testTimes[type].numObjects = numObjects;
		}

		void writeFrameTime(std::string testName, APIType type, std::int64_t frameTime)
		{
			if (type == None)
				return;
			results[testName].testTimes[type].frameTimes.push_back(frameTime);
		}

		void printResults()
		{
			for (auto& [name, result] : results)
			{
				std::filesystem::path testPath = std::filesystem::path(fullPath).parent_path()/(name+fileName);
				std::ofstream file;
				file.open(testPath);
				file << result.serialize() << std::endl;
				file.close();
			}

			results.clear();
		}
	};

	class Renderer : public core::System<core::transform, sprite_renderer, core::exampleComp>
	{
	public:
		RenderInterface* m_api;

		static std::vector<std::unique_ptr<rendering_test>> m_testScenes;
		static int currentScene;
		static int lastScene;

		static bool initializeTest;
		static bool updateTest;
		static bool stopTest;

		bool enableTesting = false;

#if RenderingAPI == RenderingAPI_OGL
		CSVWriter writer = CSVWriter("resources/logs/ogldata.csv");
#elif RenderingAPI == RenderingAPI_DX11
		CSVWriter writer = CSVWriter("resources/logs/dx11data.csv");
#endif
		int testCount = 0;
#ifdef _DEBUG
		float maxTests = 10000.0f;
#else
		float maxTests = 10000.0f;
#endif
		float timeSum = 0.0f;

		Renderer() = default;
		virtual ~Renderer() = default;

		void setup() override;
		void update() override;
		void shutdown() override;

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
				case GLFW_KEY_1:
					ShaderCache::reloadShaders();
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

		void nextScene()
		{
			key_callback(nullptr, GLFW_KEY_RIGHT, 0, GLFW_PRESS, 0);
		}

		void previousScene()
		{
			key_callback(nullptr, GLFW_KEY_LEFT, 0, GLFW_PRESS, 0);
		}
	};
}