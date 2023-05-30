#pragma once
#include <chrono>
#include <ctime>

#include <rythe/delegate>

#include "core/ecs/ecs.hpp"
#include "rendering/data/definitions.hpp"

namespace rythe::rendering
{
	using function_delegate = rsl::delegate<void(inputlayout*, RenderInterface*)>;
	using function_ptr = void(*)(inputlayout*, RenderInterface*);
	struct rendering_test
	{
	private:
		function_delegate m_setupFunc;
		function_delegate m_updateFunc;
		function_delegate m_destroyFunc;
		inputlayout layout;

		float setupTime = 0;
		float destroyTime = 0;
		float updateTimeSum = 0;
		float updateCount = 0;

	public:
		rendering_test() = default;
		rendering_test(const rendering_test& test)
		{
			m_setupFunc = test.m_setupFunc;
			m_updateFunc = test.m_updateFunc;
			m_destroyFunc = test.m_destroyFunc;
			layout = test.layout;
		}
		rendering_test(function_ptr setup, function_ptr update, function_ptr destroy)
		{
			m_setupFunc = setup;
			m_updateFunc = update;
			m_destroyFunc = destroy;
		}

		void setup(RenderInterface* api)
		{
			auto startTime = std::chrono::high_resolution_clock::now();
			m_setupFunc(&layout, api);
			auto endTime = std::chrono::high_resolution_clock::now();
			auto dur = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
			setupTime = dur.count() / 1000.0f;
		}

		void update(RenderInterface* api)
		{
			auto startTime = std::chrono::high_resolution_clock::now();
			m_updateFunc(&layout, api);
			auto endTime = std::chrono::high_resolution_clock::now();
			auto dur = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
			updateTimeSum += dur.count() / 1000.0f;
			updateCount++;
		}

		void destroy(RenderInterface* api)
		{
			auto startTime = std::chrono::high_resolution_clock::now();
			m_destroyFunc(&layout, api);
			auto endTime = std::chrono::high_resolution_clock::now();
			auto dur = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
			destroyTime = dur.count() / 1000.0f;

			log::info("Setup time: {}ms", setupTime);
			log::info("Avg Update time: {}ms", updateTimeSum / updateCount);
			log::info("Destroy Time: {}ms", destroyTime);

			setupTime = 0;
			updateTimeSum = 0;
			updateCount = 0;
			destroyTime = 0;
		}
	};
}