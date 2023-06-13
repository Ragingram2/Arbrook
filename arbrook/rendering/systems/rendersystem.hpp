#pragma once
#include <chrono>
#include <ctime>
#include <memory>
#include <iostream>

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

		std::string serialize()
		{
			std::string times;

			for (auto& [t, resultTime] : testTimes)
			{
				if (t == APIType::None)
					continue;
				times.append(std::format(",{}", resultTime.frameTime));
			}
			return times;
		}

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
			fileName = path.substr(idx, path.size() - 1);
			filePath = path.substr(0, idx);
		}

		void writeSetupTime(std::string testName, APIType type, float setupTime)
		{
			if (type == None)
				return;
			results[testName].testTimes[type].setupTime = setupTime;
		}

		void writeFrameTime(std::string testName, APIType type, float frameTime)
		{
			if (type == None)
				return;
			results[testName].testTimes[type].frameTime = frameTime;
		}

		void printResults()
		{
			std::ofstream file;
			file.open(fullPath);
			file << "APIS,";
			for (auto& [type, _] : results.begin()->second.testTimes)
				file << stringify(type) << ",";
			file << std::endl;

			for (auto& [name, result] : results)
			{
				log::debug("Results for test \"{}\"", name);
				result.printResult();
				file << name << result.serialize() << std::endl;
			}
			file.close();

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

#if RenderingAPI == RenderingAPI_OGL
		CSVWriter writer = CSVWriter("resources/logs/ogldata.csv");
#elif RenderingAPI == RenderingAPI_DX11
		CSVWriter writer = CSVWriter("resources/logs/dx11data.csv");
#endif
		int testCount = 0;
		float maxTests = 5000.0f;
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