#pragma once
#include <memory>
#include <unordered_map>
#include <queue>

#include <rsl/primitives>

#include "core/ecs/entity.hpp"
#include "core/ecs/component_family.hpp"
#include "core/engine/services/service.hpp"
#include "core/containers/pointer.hpp"

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
		static std::unordered_map<componentId, std::string> componentNames;

		Registry() = default;
		virtual ~Registry() = default;

		void initialize() override;
		void update() override;
		void shutdown() override;

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
		static componentType& createComponent(ecs::entity& ent, componentType&& value);
		template<typename componentType>
		static componentType& createComponent(rsl::id_type id, componentType&& value);
		template<typename componentType>
		static componentType& createComponent(ecs::entity& ent, const componentType& value);
		template<typename componentType>
		static componentType& createComponent(rsl::id_type id, const componentType& value);

		static void createComponent(ecs::entity& ent, rsl::id_type compId);
		static void createComponent(rsl::id_type id, rsl::id_type compId);

		template<typename componentType>
		static componentType& getComponent(ecs::entity& ent);
		template<typename componentType>
		static componentType& getComponent(rsl::id_type id);

		template<typename componentType>
		static bool hasComponent(ecs::entity& ent);
		template<typename componentType>
		static bool hasComponent(rsl::id_type id);

		static bool hasComponent(ecs::entity& ent, rsl::id_type compId);
		static bool hasComponent(rsl::id_type id, rsl::id_type compId);

		template<typename componentType>
		static void destroyComponent(ecs::entity& ent);
		template<typename componentType>
		static void destroyComponent(rsl::id_type id);
	};

	template<typename componentType>
	inline void Registry::registerComponent()
	{
		static rsl::id_type typeId = rsl::type_id<componentType>();
		if (!componentFamilies.contains(typeId))
		{
			componentFamilies.emplace(typeId, std::make_unique<component_family<componentType>>());
			auto typeName = std::string(rsl::type_name<componentType>());
			size_t pos = 0;
			while ((pos = typeName.find("::")) != std::string::npos) {
				typeName.erase(0, pos + 2);
			}
			componentNames.emplace(typeId, typeName);
			getFamily<componentType>().reserve(100);
		}
	}

	template<typename componentType>
	inline component_family<componentType>& Registry::getFamily()
	{
		static rsl::id_type typeId = rsl::type_id<componentType>();
		return *reinterpret_cast<component_family<componentType>*>(componentFamilies[typeId].get());
	}

	template<typename componentType>
	inline componentType& Registry::createComponent(ecs::entity& ent)
	{
		return createComponent<componentType>(ent.data->id);
	}
	template<typename componentType>
	inline componentType& Registry::createComponent(rsl::id_type id)
	{
		static rsl::id_type typeId = rsl::type_id<componentType>();
		//Register component with the registry
		if (!componentFamilies.contains(typeId))
		{
			ecs::Registry::registerComponent<componentType>();
		}

		//Registry component with the entity
		if (!entityCompositions.contains(id))
			entityCompositions.emplace(id, std::unordered_set<rsl::id_type>());

		entityCompositions.at(id).emplace(typeId);

		return *reinterpret_cast<componentType*>(getFamily<componentType>().createComponent(id).ptr);
	}

	template<typename componentType>
	inline componentType& Registry::createComponent(ecs::entity& ent, componentType&& value)
	{
		return createComponent<componentType>(ent.data->id, value);
	}

	template<typename componentType>
	inline componentType& Registry::createComponent(rsl::id_type id, componentType&& value)
	{
		static rsl::id_type typeId = rsl::type_id<componentType>();
		//Register component with the registry
		if (!componentFamilies.contains(typeId))
		{
			ecs::Registry::registerComponent<componentType>();
		}

		//Registry component with the entity
		if (!entityCompositions.contains(id))
			entityCompositions.emplace(id, std::unordered_set<rsl::id_type>());

		entityCompositions.at(id).emplace(typeId);

		return *reinterpret_cast<componentType*>(getFamily<componentType>().createComponent(id, std::forward<componentType>(value)).ptr);
	}

	template<typename componentType>
	inline componentType& Registry::createComponent(ecs::entity& ent, const componentType& value)
	{
		return createComponent<componentType>(ent.data->id, value);
	}

	template<typename componentType>
	inline componentType& Registry::createComponent(rsl::id_type id, const componentType& value)
	{
		static rsl::id_type typeId = rsl::type_id<componentType>();
		//Register component with the registry
		if (!componentFamilies.contains(typeId))
		{
			ecs::Registry::registerComponent<componentType>();
		}

		//Registry component with the entity
		if (!entityCompositions.contains(id))
			entityCompositions.emplace(id, std::unordered_set<rsl::id_type>());

		entityCompositions.at(id).emplace(typeId);

		return *reinterpret_cast<componentType*>(getFamily<componentType>().createComponent(id, value).ptr);
	}

	inline void Registry::createComponent(ecs::entity& ent, rsl::id_type compId)
	{
		createComponent(ent.data->id, compId);
	}

	inline void Registry::createComponent(rsl::id_type id, rsl::id_type compId)
	{
		//Register component with the registry
		if (!componentFamilies.contains(compId))
		{
			log::error("Cannot deduce component type from id");
		}
		//Registry component with the entity
		if (!entityCompositions.contains(id))
			entityCompositions.emplace(id, std::unordered_set<rsl::id_type>());

		entityCompositions.at(id).emplace(compId);
		componentFamilies[compId].get()->createComponent(id);
	}

	template<typename componentType>
	inline componentType& Registry::getComponent(ecs::entity& ent)
	{
		return *reinterpret_cast<componentType*>(getFamily<componentType>().getComponent(ent).ptr);
	}
	template<typename componentType>
	inline componentType& Registry::getComponent(rsl::id_type id)
	{
		return *reinterpret_cast<componentType*>(getFamily<componentType>().getComponent(id).ptr);
	}

	template<typename componentType>
	inline bool Registry::hasComponent(ecs::entity& ent)
	{
		return hasComponent<componentType>(ent.data->id);
	}
	template<typename componentType>
	inline bool Registry::hasComponent(rsl::id_type id)
	{
		rsl::id_type typeId = rsl::type_id<componentType>();
		auto& vec = entityCompositions.at(id);
		auto position = std::find(vec.begin(), vec.end(), typeId);
		if (position != vec.end())
			return true;
		return false;
	}

	template<typename componentType>
	inline void Registry::destroyComponent(ecs::entity& ent)
	{
		destroyComponent<componentType>(ent.data->id);
	}
	template<typename componentType>
	inline void Registry::destroyComponent(rsl::id_type id)
	{
		if (entityCompositions.contains(id))
		{
			rsl::id_type typeId = rsl::type_id<componentType>();
			auto& vec = entityCompositions.at(id);
			auto position = std::find(vec.begin(), vec.end(), typeId);
			if (position != vec.end())
				vec.erase(position);
		}

		auto& family = getFamily<componentType>();
		family.destroyComponent(id);
	}
}


#include "core/ecs/entity.inl"