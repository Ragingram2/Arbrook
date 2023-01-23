#pragma once
#include <memory>
#include <iostream>
#include <unordered_map>
#include <string>

#include <rythe/primitives>

#include "engine/services/service.hpp"
#include "containers/pointer.hpp"

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

#include "engine/services/serviceregistry.inl"