#pragma once
#include <memory>
#include <iostream>
#include <unordered_map>
#include <string>

#include "engine/services/service.hpp"
#include "types/types.hpp"
#include "containers/pointer.hpp"

namespace rythe::core
{
	class ServiceRegistry
	{
	public:
		std::unordered_map<id_type, std::unique_ptr<Service>> m_services;
		ServiceRegistry() = default;
		~ServiceRegistry() = default;

		template<typename serviceType = Service,typename... Args>
		pointer<serviceType> register_service(Args&&... args);
		template<typename serviceType = Service>
		void remove_service();
		template<typename serviceType = Service>
		pointer<serviceType> get_service();
	};

}

#include "engine/services/serviceregistry.inl"