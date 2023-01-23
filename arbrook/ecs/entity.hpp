#pragma once
#include <format>
#include <rythe/primitives>

namespace rythe::core::ecs
{
	struct entity
	{
		//ecs::entity parent;
		rsl::id_type m_id = -1;
		std::string m_name = "";

		entity() = default;
		entity(const ecs::entity& ent) : m_id(ent.m_id), m_name(ent.m_name) {}
		entity(rsl::id_type id) : m_id(id), m_name(std::format("Entity {}", m_id)) {}
		entity(rsl::id_type id, std::string name) : m_id(id), m_name(name) {}
		~entity() = default;
	};
}