#pragma once
#include <unordered_map>
#include <any>

#include <rsl/primitives>
#include <rsl/hash>

#include "core/containers/pointer.hpp"
#include "core/ecs/entity.hpp"

namespace rythe::core::ecs
{
	struct component_family_base
	{
		using entityId = rsl::id_type;
		rsl::id_type m_typeId = 0;

		component_family_base(rsl::id_type id) : m_typeId(id) {}

		virtual void reserve(rsl::size_type amount) RYTHE_PURE;

		virtual void clear() RYTHE_PURE;

		virtual pointer<void> createComponent(entity& ent) RYTHE_PURE;
		virtual pointer<void> createComponent(entityId id) RYTHE_PURE;

		virtual pointer<void> getComponent(entity& ent) RYTHE_PURE;
		virtual pointer<void> getComponent(entityId id) RYTHE_PURE;

		virtual void destroyComponent(entityId id) RYTHE_PURE;

		virtual ~component_family_base() = default;
	};
}