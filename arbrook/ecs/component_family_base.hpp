#pragma once
#include <unordered_map>
#include <any>

#include <rythe/primitives>
#include <rythe/hash>

#include "containers/pointer.hpp"
#include "ecs/entity.hpp"
//#include "ecs/component_base.hpp"

namespace rythe::core::ecs
{
	struct component_family_base
	{
		using entityId = rsl::id_type;
		rsl::id_type m_typeId = 0;
		std::unordered_map<entityId, std::any> m_componentData;
		component_family_base(rsl::id_type id) : m_typeId(id) {}

		std::any& createComponent(entity& ent);
		std::any& createComponent(entityId id);

		std::any& getComponent(entity& ent);
		std::any& getComponent(entityId id);

		void destroyComponent(entityId id);
	};
}