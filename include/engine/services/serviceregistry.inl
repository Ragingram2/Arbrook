#include "engine/services/serviceregistry.hpp"
#pragma once

namespace rythe::core
{
	template<typename serviceType, typename... Args>
	pointer<serviceType> ServiceRegistry::register_service(Args&&... args)
	{
		auto [iterator, emplace] = m_services.try_emplace(typeHash<serviceType>(), std::make_unique<serviceType>(std::forward<Args>(args)...));
		return { dynamic_cast<serviceType*>(iterator->second.get()) };
	}

	template<typename serviceType>
	void ServiceRegistry::remove_service()
	{

	}

	template<typename serviceType>
	pointer<serviceType> ServiceRegistry::get_service()
	{
		const id_type typeId = typeHash<serviceType>();
		if (m_services.count(typeId))
			return { dynamic_cast<serviceType*>(m_services.at(typeId).get()) }
		return { nullptr };
	}
}