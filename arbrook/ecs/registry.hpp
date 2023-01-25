#pragma once
#include <memory>
#include <unordered_map>
#pragma once
#include <queue>

#include <rythe/primitives>

#include "ecs/entity.hpp"
#include "ecs/component.hpp"
#include "engine/services/service.hpp"
#include "containers/pointer.hpp"

namespace rythe::core::ecs
{
	class Registry : public Service
	{
	public:
		rsl::id_type m_lastId = 0;
		static std::unordered_map<rsl::id_type, ecs::entity > m_entities;
		std::unordered_map<rsl::id_type, std::vector<std::unique_ptr<component_base>>> m_componentPools;

		Registry() = default;
		virtual ~Registry() = default;

		void initialize() override {}
		void update() override {}
		void shutdown() override {}

		ecs::entity& createEntity();
		ecs::entity& createEntity(const std::string& name);

		void destroyEntity(ecs::entity& ent);
		void destroyEntity(rsl::id_type id);

		//template<typename componentType>
		//pointer<componentType>  addComponent(ecs::entity& ent);
		//template<typename componentType>
		//pointer<componentType>  addComponent(rsl::id_type id);

		//template<typename componentType>
		//void removeComponent(ecs::entity& ent);
		//template<typename componentType>
		//void removeComponent(rsl::id_type id);
	};
}

#include "ecs/registry.inl"