#include "engine/services/serviceregistry.hpp"
#pragma once

namespace rythe::core
{
	template<typename serviceType>
	pointer<serviceType> ServiceRegistry::register_service()
	{
		auto [iterator, emplace] = m_services.emplace(rsl::typeHash<serviceType>(), std::make_unique<serviceType>());
		return { dynamic_cast<serviceType*>(iterator->second.get()) };
	}

	template<typename serviceType>
	void ServiceRegistry::remove_service()
	{

	}

	template<typename serviceType>
	pointer<serviceType> ServiceRegistry::get_service()
	{
		const rsl::id_type typeId = rsl::typeHash<serviceType>();
		if (m_services.count(typeId))
			return { dynamic_cast<serviceType*>(m_services.at(typeId).get()) };
		return { nullptr };
	}
}