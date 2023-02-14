#pragma once
#include "events/event.hpp"
#include "ecs/entity.hpp"

namespace rythe::core::events
{
	template<typename componentType>
	struct component_creation : public event<component_creation<componentType>>
	{
		ecs::entity entity;

		component_creation() = default;
		component_creation(ecs::entity entity) : entity(entity) {}
		component_creation(rsl::id_type entId) : entity(entId) {}
	};

	template<typename componentType>
	struct component_destruction : public event<component_destruction<componentType>>
	{
		ecs::entity entity;

		component_destruction() = default;
		component_destruction(ecs::entity entity) : entity(entity) {}
		component_destruction(rsl::id_type entId) : entity(entId) {}
	};
}