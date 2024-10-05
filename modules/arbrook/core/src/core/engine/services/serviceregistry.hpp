#pragma once
#include <memory>
#include <iostream>
#include <unordered_map>
#include <string>

#include <rsl/primitives>
#include <rsl/hash>

#include "core/engine/services/service.hpp"
#include "core/containers/pointer.hpp"

namespace rythe::core
{
	class ServiceRegistry
	{
	public:
		std::unordered_map<rsl::id_type, std::unique_ptr<Service>> m_services;
		ServiceRegistry() {}
		MOVE_FUNCS(ServiceRegistry)
		~ServiceRegistry() = default;

		template<typename serviceType>
		pointer<serviceType> register_service();
		template<typename serviceType>
		void remove_service();
		template<typename serviceType>
		pointer<serviceType> get_service();
	};
}

#include "core/engine/services/serviceregistry.inl"