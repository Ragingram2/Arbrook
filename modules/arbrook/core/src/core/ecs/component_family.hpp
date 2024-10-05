#pragma once
#include <memory>
#include <unordered_map>
#include <queue>
#include <any>

#include <rsl/primitives>
#include <rsl/hash>

#include "core/ecs/component_container.hpp"
#include "core/ecs/component_family_base.hpp"
#include "core/ecs/entity.hpp"
#include "core/containers/pointer.hpp"
#include "core/events/eventbus.hpp"
#include "core/events/defaults/component_event.hpp"
#include "core/common/meta.hpp"

namespace rythe::core::ecs
{
	template<typename componentType>
	struct component_family : public component_family_base
	{
		using entityId = rsl::id_type;
		using type = componentType;

		std::unordered_map<entityId, componentType> m_components;
		component_family() : component_family_base(rsl::typeHash<componentType>()) {}
		component_family(std::nullptr_t t) : component_family_base(0) { }
		~component_family() = default;

		virtual void reserve(rsl::size_type amount);

		virtual void clear();

		virtual pointer<void> createComponent(entity& ent);
		virtual pointer<void> createComponent(entityId id);

		virtual pointer<void> createComponent(entity& ent, componentType&& value);
		virtual pointer<void> createComponent(entityId id, componentType&& value);

		virtual pointer<void> createComponent(entity& ent, const componentType& value);
		virtual pointer<void> createComponent(entityId id, const componentType& value);

		virtual pointer<void> getComponent(entity& ent);

		virtual pointer<void> getComponent(entityId id);

		virtual void destroyComponent(entity& id);

		virtual void destroyComponent(entityId id);

		//virtual void fillContainer(component_container<componentType>& container, std::vector<entity> entities);
	};
}
//HAS_MEMBER(m_owner);

#include "core/ecs/component_family.inl"