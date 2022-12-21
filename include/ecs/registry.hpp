#pragma once
#include <memory>
#include <unordered_map>
#include <queue>

#include "data/entity_data.hpp"

namespace rythe::core::ecs
{
	static constexpr id_type world_entity_id = 1;

	class Registry
	{
	private:
		std::unordered_map<id_type, entity_data> m_entities;
		std::queue<id_type> m_recyclableEntities;

		id_type m_nextEntityId = world_entity_id + 1;

		R_NODISCARD static id_type getNextEntityId();

	public:
		R_NODISCARD static entity getWorld();

		R_NODISCARD static entity createEntity();
		R_NODISCARD static entity createEntity(const std::string& name);

		static void destroyEntity(entity target, bool  recruse = true);
		static void destroyEntity(id_type target, bool recurse = true);

		R_NODISCARD static bool checkEntity(id_type target);
		
		R_NODISCARD static entity_data& entityData(id_type target);
		R_NODISCARD static entity getEntity(id_type target);
	};
}