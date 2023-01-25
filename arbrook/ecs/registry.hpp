#pragma once
#include <memory>
#include <unordered_map>
#pragma once
#include <queue>

#include <rythe/primitives>
#include <rythe/hash>

#include "ecs/entity.hpp"
#include "ecs/component.hpp"
#include "ecs/componentpool.hpp"
#include "engine/services/service.hpp"
#include "containers/pointer.hpp"

namespace rythe::core::ecs
{
	class Registry : public Service
	{
	public:
		rsl::id_type m_lastId = 0;
		static std::unordered_map<rsl::id_type, ecs::entity > m_entities;
		static std::unordered_map<rsl::id_type, std::unique_ptr<component_pool_base>> m_componentPools;

		Registry() = default;
		virtual ~Registry() = default;

		void initialize() override {}
		void update() override {}
		void shutdown() override {}

		ecs::entity& createEntity();
		ecs::entity& createEntity(const std::string& name);

		void destroyEntity(ecs::entity& ent);
		void destroyEntity(rsl::id_type id);

		template<typename componentType>
		pointer<componentType>  getComponent(ecs::entity& ent);
		template<typename componentType>
		pointer<componentType>  getComponent(rsl::id_type id);

		template<typename componentType>
		bool  hasComponent(ecs::entity& ent);
		template<typename componentType>
		bool  hasComponent(rsl::id_type id);

		template<typename componentType>
		void destroyComponent(ecs::entity& ent);
		template<typename componentType>
		void  destroyComponent(rsl::id_type id);
	};
}

#include "ecs/registry.inl"