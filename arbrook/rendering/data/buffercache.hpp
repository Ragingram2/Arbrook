#pragma once
#include <string>
#include <memory>
#include <unordered_map>

#include "core/core.hpp"
#include "rendering/data/bufferhandle.hpp"
#include "rendering/data/definitions.hpp"

namespace rythe::rendering
{
	class BufferCache
	{
	private:
		static RenderInterface m_api;
		static std::unordered_map<std::string, std::unique_ptr<buffer>> m_buffers;
	public:
		template<typename dataType>
		static buffer_handle createBuffer(const std::string& name, TargetType target, UsageType usage, dataType* data = nullptr, int size = 0);
		static buffer_handle getBuffer(const std::string& name);
		static void deleteBuffer(const std::string& name);
	};
}