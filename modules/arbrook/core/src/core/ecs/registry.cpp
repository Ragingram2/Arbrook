#include "../ecs/registry.hpp"

namespace rythe::core::ecs
{
	using entityId = rsl::id_type;
	using componentId = rsl::id_type;

	std::unordered_map<entityId, ecs::entity_data> Registry::entities;
	std::unordered_map<entityId, std::unordered_set<rsl::id_type>> Registry::entityCompositions;
	std::unordered_map<componentId, std::unique_ptr<component_family_base>> Registry::componentFamilies;
	std::unordered_map<componentId, std::string> Registry::componentNames;

	ecs::entity Registry::createEntity()
	{
		lastId++;
		auto& [_, data] = *entities.try_emplace(lastId).first;
		data.alive = true;
		data.id = lastId;
		data.name = std::format("Entity {}", lastId);
		data.parent = ecs::entity{ world };

		entityCompositions.try_emplace(ecs::entity{ &data });
		return ecs::entity{ &data };
	}

	ecs::entity Registry::createEntity(ecs::entity parent)
	{
		lastId++;
		auto& [_, data] = *entities.try_emplace(lastId).first;
		data.alive = true;
		data.id = lastId;
		data.name = std::format("Entity {}", lastId);
		data.parent = parent;

		if (parent)
			parent->children.insert(ecs::entity{ &data });

		entityCompositions.try_emplace(ecs::entity{ &data });
		return ecs::entity{ &data };
	}

	ecs::entity Registry::createEntity(const std::string& name)
	{
		lastId++;
		auto& [_, data] = *entities.try_emplace(lastId).first;
		data.alive = true;
		data.id = lastId;
		data.name = name;
		data.parent = ecs::entity{ world };
		return ecs::entity{ &data };
	}

	void Registry::destroyEntity(ecs::entity& ent)
	{
		for (auto typeId : entityCompositions[ent->id])
		{
			destroyComponent(ent, typeId);
		}

		entityCompositions.erase(ent->id);
		entities.erase(ent->id);
	}

	void Registry::destroyEntity(rsl::id_type id)
	{
		for (auto typeId : entityCompositions[id])
		{
			destroyComponent(id, typeId);
		}

		entityCompositions.erase(id);
		entities.erase(id);
	}

	bool Registry::hasComponent(ecs::entity& ent, rsl::id_type compId)
	{
		return hasComponent(ent->id, compId);
	}

	bool Registry::hasComponent(rsl::id_type id, rsl::id_type compId)
	{
		auto& vec = entityCompositions.at(id);
		auto position = std::find(vec.begin(), vec.end(), compId);
		if (position != vec.end())
			return true;
		return false;
	}

	void Registry::destroyComponent(ecs::entity& ent, rsl::id_type componentId)
	{
		auto family = componentFamilies[componentId].get();
		family->destroyComponent(ent->id);
	}

	void Registry::destroyComponent(rsl::id_type id, rsl::id_type componentId)
	{
		auto family = componentFamilies[componentId].get();
		family->destroyComponent(id);
	}

	//component_family_base* Registry::getFamily(rsl::id_type typeId)
	//{
	//	return reinterpret_cast<component_family_base*>(m_componentFamilies[typeId].get());
	//}
}