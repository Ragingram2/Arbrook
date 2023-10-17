#pragma once
#include <string>
#include <memory>
#include <unordered_map>

#include "core/logging/logging.hpp"

#include "rendering/data/bufferhandle.hpp"
#include "rendering/interface/buffer.hpp"


namespace rythe::rendering
{
	class BufferCache
	{
	private:
		static std::unordered_map<std::string, std::unique_ptr<buffer>> m_buffers;
	public:
		template<typename elementType>
		static buffer_handle createBuffer(const std::string& name, TargetType target, UsageType usage, std::vector<elementType> data);
		template<typename elementType>
		static buffer_handle createBuffer(const std::string& name, TargetType target, UsageType usage = UsageType::STATICDRAW, elementType* data = nullptr, int size = 1);
		static buffer_handle getBuffer(const std::string& name);
		static void deleteBuffer(const std::string& name);
	};

	template<typename elementType>
	inline buffer_handle BufferCache::createBuffer(const std::string& name, TargetType target, UsageType usage, std::vector<elementType> data)
	{
		return { createBuffer(name, target, usage,data.data(),data.size()) };
	}

	template<typename elementType>
	inline buffer_handle BufferCache::createBuffer(const std::string& name, TargetType target, UsageType usage, elementType* data, int size)
	{
		if (m_buffers.contains(name))
		{
			return m_buffers[name].get();
		}

		auto buff = m_buffers.emplace(name, std::make_unique<buffer>()).first->second.get();
		buff->m_impl.name = name;
		buff->initialize<elementType>(target, usage, size);
		if (data)
		{
			buff->bufferData<elementType>(data, size);
		}
		return { buff };
	}
}