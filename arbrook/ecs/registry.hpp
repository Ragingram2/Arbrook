#pragma once
#include <memory>
#include <unordered_map>
#pragma once
#include <queue>

#include <rythe/primitives>
#include <rythe/hash>

#include "ecs/entity.hpp"
#include "ecs/component.hpp"
//#include "ecs/componentpool.hpp"
#include "engine/services/service.hpp"
#include "containers/pointer.hpp"

namespace rythe::core::ecs
{
	struct component_family_base
	{
		rsl::id_type m_typeId;
	};

	template<typename componentType>
	struct component_family : public component_family_base
	{
		using entityId = rsl::id_type;
		std::unordered_map<entityId, componentType> m_components;
		component_family()
		{
			m_typeId = rsl::typeHash<componentType>();
		}

		componentType* createComponent(entity& ent);

		componentType* createComponent(entityId id);

		componentType& getComponent(entity& ent);

		componentType& getComponent(entityId id);
	};

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

		template<typename componentType>
		static void registerComponent();

		template<typename componentType>
		static component_family<componentType>& getFamily();

		template<typename componentType>
		static componentType* createComponent(ecs::entity& ent);
		template<typename componentType>
		static componentType* createComponent(rsl::id_type id);

		template<typename componentType>
		static componentType& getComponent(ecs::entity& ent);
		template<typename componentType>
		static componentType& getComponent(rsl::id_type id);

		//template<typename componentType>
		//bool  hasComponent(ecs::entity& ent);
		//template<typename componentType>
		//bool  hasComponent(rsl::id_type id);

		//template<typename componentType>
		//void destroyComponent(ecs::entity& ent);
		//template<typename componentType>
		//void  destroyComponent(rsl::id_type id);
	};
}

#include "ecs/registry.inl"