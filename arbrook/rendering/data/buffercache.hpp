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
		static std::unordered_map<std::string, std::unique_ptr<buffer>> m_buffers;
	public:
		template<typename elementType, typename dataType = elementType>
		static buffer_handle createBuffer(RenderInterface& api, const std::string& name, TargetType target, UsageType usage, elementType* data = nullptr, int size = 1);
		static buffer_handle getBuffer(const std::string& name);
		static void deleteBuffer(const std::string& name);
	};

	template<typename elementType, typename dataType>
	inline buffer_handle BufferCache::createBuffer(RenderInterface& api, const std::string& name, TargetType target, UsageType usage, elementType* data, int size)
	{
		if (m_buffers.contains(name))
		{
			log::warn("Buffer {} already exists, ignoring new buffer, and returning existing one", name);
			return m_buffers[name].get();
		}

		auto buff = m_buffers.emplace(name, std::make_unique<buffer>()).first->second.get();
		buff->m_impl.name = name;

		return api.createBuffer<elementType, dataType>(buff, target, usage, data, size);
	}
}