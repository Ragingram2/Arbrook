#pragma once
#include <rsl/logging>

namespace rythe
{
	namespace log = rsl::log;

	inline static std::shared_ptr<spdlog::sinks::ringbuffer_sink_mt> appConsoleSink = std::make_shared<spdlog::sinks::ringbuffer_sink_mt>(2048);
}
