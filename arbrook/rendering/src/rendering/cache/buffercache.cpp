#include "rendering/cache/buffercache.hpp"

namespace rythe::rendering
{
	std::unordered_map<std::string, std::unique_ptr<buffer>> BufferCache::m_buffers;

	buffer_handle BufferCache::getBuffer(const std::string& name)
	{
		if (m_buffers.contains(name))
		{
			return m_buffers[name].get();
		}
		log::warn("Buffer {} does not exist", name);
		return buffer_handle{};
	}

	void BufferCache::deleteBuffer(const std::string& name)
	{
		if (m_buffers.contains(name))
		{
			m_buffers[name]->release();
			m_buffers.erase(name);
		}
	}
}