#pragma once
#include <unordered_map>

#include <rythe/primitives>

#include "platform/platform.hpp"
#include "ecs/component.hpp"
#include "ecs/entity.hpp"
#include "containers/pointer.hpp"

namespace rythe::core::ecs
{
	struct component_pool_base
	{
		virtual void reserve(rsl::size_type amount) RYTHE_PURE;
		virtual void clear() RYTHE_PURE;
		virtual pointer<component_base> create_component(entity target) RYTHE_PURE;
		R_NODISCARD virtual bool contains(entity target) const RYTHE_PURE;
		R_NODISCARD virtual pointer<component_base> get_component(entity target) RYTHE_PURE;
		R_NODISCARD virtual const pointer<component_base> get_component(entity target) const RYTHE_PURE;
		virtual void destroy_component(entity target) RYTHE_PURE;
		virtual ~component_pool_base() = default;
	};

	template<typename componentType>
	struct component_pool : public component_pool_base
	{
		std::unordered_map<rsl::id_type, componentType> m_components{ 125 };

		virtual void reserve(rsl::size_type amount);
		virtual void clear();
		R_NODISCARD virtual bool contains(entity target) const;

		virtual pointer<component_base> create_component(entity target);
		template<typename... Args>
		componentType& create_component(entity target, Args&&... args);

		R_NODISCARD virtual pointer<component_base> get_component(entity target);
		R_NODISCARD virtual const pointer<component_base> get_component(entity target) const;

		virtual void destroy_component(entity target);
		virtual ~component_pool() = default;
	}
}