#pragma once
#include "core/events/event.hpp"
#include "core/ecs/entity.hpp"

namespace rythe::core::events
{
	template<typename componentType>
	struct component_creation : public event<component_creation<componentType>>
	{
		rsl::id_type entId;

		component_creation() = default;
		component_creation(ecs::entity ent)
		{
			entId = ent->id;
		}
		component_creation(rsl::id_type id) 
		{
			entId = id;
		}
	};

	template<typename componentType>
	struct component_destruction : public event<component_destruction<componentType>>
	{
		rsl::id_type entId;

		component_destruction() = default;
		component_destruction(ecs::entity ent) 
		{
			entId = ent->id;
		}
		component_destruction(rsl::id_type id)
		{
			entId = id;
		}
	};
}