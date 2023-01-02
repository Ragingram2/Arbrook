#pragma once
#include <memory>
#include <unordered_set>

#include "ecs/handles/entity.hpp"


namespace rythe::core::ecs
{
	/**entity_data
	 *  Entity specific data, eg: alive, active, children.
	 */
	struct entity_data
	{
		//entity state bitfield
		bool alive : 1;//bool only needs 1 bit
		bool active : 1;

		id_type id = invalid_id;

		std::string name;
		entity parent = { nullptr };
		std::vector<entity> children;
	};
}
