#pragma once
#include <memory>
#include <unordered_map>
#include <queue>
#include <any>

#include <rythe/primitives>
#include <rythe/hash>

#include "ecs/component_family_base.hpp"
#include "ecs/entity.hpp"
#include "containers/pointer.hpp"

namespace rythe::core::ecs
{
	template<typename componentType>
	struct component_family : public component_family_base
	{
		using entityId = rsl::id_type;
		//std::unordered_map<entityId, componentType> m_components;
		component_family() : component_family_base(rsl::typeHash<componentType>()) {}
		component_family(std::nullptr_t t) : component_family_base(0) { }
		~component_family() = default;

		inline componentType& createComponent(entity& ent);

		inline componentType& createComponent(entityId id);

		inline componentType& getComponent(entity& ent);

		inline componentType& getComponent(entityId id);

		inline void destroyComponent(entity& ent);

		inline void destroyComponent(entityId id);
	};
}

#include "ecs/component_family.inl"