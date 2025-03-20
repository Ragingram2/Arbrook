#include "core/ecs/registry.hpp"
#include "core/components/transform.hpp"
namespace rythe::core::ecs
{
	using entityId = rsl::id_type;
	using componentId = rsl::id_type;

	std::unordered_map<entityId, ecs::entity_data> Registry::entities;
	std::unordered_map<entityId, std::unordered_set<rsl::id_type>> Registry::entityCompositions;
	std::unordered_map<componentId, std::unique_ptr<component_family_base>> Registry::componentFamilies;
	std::unordered_map<componentId, std::string> Registry::componentNames;


	void Registry::initialize()
	{
		log::info("Initializing world entity");
		auto& [_, ent] = *entities.try_emplace(worldId).first;
		ent.alive = true;
		ent.id = worldId;
		ent.name = "World";
		entityCompositions.try_emplace(worldId);
		world = entity{ &ent };
		auto& transf = world.addComponent<transform>();
		transf.position = math::vec3(0.0f);
		transf.rotation = math::quat::identity;
		transf.scale = math::vec3(1.0f);
	}

	void Registry::update()
	{

	}

	void Registry::shutdown()
	{

	}

	ecs::entity Registry::createEntity()
	{
		lastId++;
		auto& [_, ent] = *entities.try_emplace(lastId).first;
		ent.alive = true;
		ent.id = lastId;
		ent.name = std::format("Entity {}", lastId);
		ent.parent = world;
		//world->children.emplace(ent);
		entityCompositions.try_emplace(entity{ &ent });
		return entity{ &ent };
	}

	ecs::entity Registry::createEntity(ecs::entity parent)
	{
		lastId++;
		auto& [_, ent] = *entities.try_emplace(lastId).first;
		ent.alive = true;
		ent.id = lastId;
		ent.name = std::format("Entity {}", lastId);
		ent.parent = parent;
		//if (parent)
		//	parent.data->children.insert(entity{&ent});

		entityCompositions.try_emplace(entity{ &ent });
		return entity{ &ent };
	}

	ecs::entity Registry::createEntity(const std::string& name)
	{
		lastId++;
		auto& [_, ent] = *entities.try_emplace(lastId).first;
		ent.alive = true;
		ent.id = lastId;
		ent.name = name;
		ent.parent = world;
		//world->children.emplace(ent);
		return entity{ &ent };
	}

	void Registry::destroyEntity(ecs::entity& ent)
	{
		for (auto typeId : entityCompositions[ent.data->id])
		{
			destroyComponent(ent, typeId);
		}
		entityCompositions.erase(ent.data->id);
		entities.erase(ent.data->id);
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
		return hasComponent(ent.data->id, compId);
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
		family->destroyComponent(ent.data->id);
	}

	void Registry::destroyComponent(rsl::id_type id, rsl::id_type componentId)
	{
		auto family = componentFamilies[componentId].get();
		family->destroyComponent(id);
	}
}