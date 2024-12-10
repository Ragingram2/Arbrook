#include "entity.hpp"
#include "registry.hpp"

namespace rythe::core::ecs
{
	
	entity::operator rsl::id_type() const noexcept
	{
		return (data && data->alive) ? data->id : invalid_id;
	}

	void entity::addComponent(rsl::id_type compId)
	{
		return Registry::createComponent(data->id, compId);
	}

	bool entity::hasComponent(rsl::id_type compId)
	{
		return Registry::hasComponent(data->id, compId);
	}

	std::unordered_set<rsl::id_type>& entity::component_composition()
	{
		return Registry::entityCompositions[data->id];
	}
	const std::unordered_set<rsl::id_type>& entity::component_composition() const
	{
		return Registry::entityCompositions[data->id];
	}
}