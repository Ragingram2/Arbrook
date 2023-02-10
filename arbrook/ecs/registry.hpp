#pragma once
#include <memory>
#include <unordered_map>
#include <queue>

#include <rythe/primitives>
#include <rythe/hash>

#include "ecs/entity.hpp"
#include "ecs/component.hpp"
#include "ecs/component_family_base.hpp"
#include "ecs/component_family.hpp"
#include "engine/services/service.hpp"
#include "containers/pointer.hpp"

namespace rythe::core::ecs
{
	class Registry : public Service
	{
	public:
		rsl::id_type m_lastId = 0;
		using entityId = rsl::id_type;
		using componentId = rsl::id_type;

		static std::unordered_map<entityId, ecs::entity> m_entities;
		static std::unordered_map<entityId, std::vector<rsl::id_type>> m_entityCompositions;
		static std::unordered_map<componentId, std::unique_ptr<component_family_base>> m_componentFamilies;

		Registry() = default;
		virtual ~Registry() = default;

		void initialize() override {}
		void update() override {}
		void shutdown() override {}

		ecs::entity& createEntity();
		ecs::entity& createEntity(const std::string& name);

		void destroyEntity(ecs::entity& ent);
		void destroyEntity(rsl::id_type id);

		void destroyComponent(ecs::entity& ent, rsl::id_type componentId);
		void destroyComponent(rsl::id_type id, rsl::id_type componentId);

		template<typename componentType>
		static void registerComponent();

		template<typename componentType>
		static component_family<componentType>& getFamily();

		template<typename componentType>
		static componentType& createComponent(ecs::entity& ent);
		template<typename componentType>
		static componentType& createComponent(rsl::id_type id);

		template<typename componentType>
		static componentType& getComponent(ecs::entity& ent);
		template<typename componentType>
		static componentType& getComponent(rsl::id_type id);

		template<typename componentType>
		static bool hasComponent(ecs::entity& ent);
		template<typename componentType>
		static bool hasComponent(rsl::id_type id);

		template<typename componentType>
		static void destroyComponent(ecs::entity& ent);
		template<typename componentType>
		static void destroyComponent(rsl::id_type id);
	};
}

#include "ecs/registry.inl"