#include "rendering/data/buffercache.hpp"

namespace rythe::rendering
{
	std::unordered_map<std::string, std::unique_ptr<buffer>> BufferCache::m_buffers;

	template<typename dataType>
	buffer_handle BufferCache::createBuffer(RenderInterface& api, const std::string& name, TargetType target, UsageType usage, dataType* data, int size)
	{
		if (m_buffers.contains(name))
		{
			log::warn("Buffer {} already exists, ignoring new buffer, and returning existing one", name);
			return m_buffers[name].get()->operator->();
		}

		auto buff = m_buffers.emplace(name, std::make_unique<buffer>()).first->second->operator->();

		return api.createBuffer(buff, target, usage, data, size);
	}

	buffer_handle BufferCache::getBuffer(const std::string& name)
	{
		if (m_buffers.contains(name))
		{
			return m_buffers[name].get()->operator->();
		}
		log::warn("Buffer {} does not exist", name);
		return nullptr;
	}

	void BufferCache::deleteBuffer(const std::string& name)
	{

	}
}