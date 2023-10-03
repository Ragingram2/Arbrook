#pragma once
#include <memory>
#include <unordered_map>
#include <queue>

#include <rsl/primitives>

#include "core/ecs/entity.hpp"
#include "core/ecs/entity_data.hpp"
#include "core/ecs/component.hpp"
#include "core/ecs/component_family_base.hpp"
#include "core/ecs/component_family.hpp"
#include "core/engine/services/service.hpp"
#include "core/containers/pointer.hpp"
#include "core/components/transform.hpp"

namespace rythe::core::ecs
{
	class Registry : public Service
	{
	public:
		rsl::id_type lastId = 1;
		const static rsl::id_type worldId = 1;
		entity world;
		using entityId = rsl::id_type;
		using componentId = rsl::id_type;

		static std::unordered_map<entityId, ecs::entity_data> entities;
		static std::unordered_map<entityId, std::unordered_set<rsl::id_type>> entityCompositions;
		static std::unordered_map<componentId, std::unique_ptr<component_family_base>> componentFamilies;

		Registry() = default;
		virtual ~Registry() = default;

		void initialize() override
		{
			log::debug("Initializeing world entity");
			auto& [_,data] = *entities.try_emplace(worldId).first;
			data.alive = true;
			data.id = worldId;
			data.name = "World";
			data.parent = entity{ nullptr };
			entityCompositions.try_emplace(worldId);
			world = entity{ &data };
			world.addComponent<transform>();
		}
		void update() override {}
		void shutdown() override {}

		ecs::entity createEntity();
		ecs::entity createEntity(ecs::entity parent);
		ecs::entity createEntity(const std::string& name);

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

#include "core/ecs/registry.inl"