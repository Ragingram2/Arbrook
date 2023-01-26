#pragma once
#include <format>

#include <rythe/primitives>
#include <rythe/hash>

#include "platform/platform.hpp"
#include "containers/pointer.hpp"
#include "ecs/component_base.hpp"

namespace rythe::core::ecs
{
	struct entity
	{
		//ecs::entity parent;
		rsl::id_type m_id = -1;
		std::string m_name = "";

		std::unordered_map<rsl::id_type, std::unique_ptr<component_base>> m_components;

		entity() = default;
		entity(const ecs::entity& ent) : m_id(ent.m_id), m_name(ent.m_name) {}
		entity(rsl::id_type id) : m_id(id), m_name(std::format("Entity {}", m_id)) {}
		entity(rsl::id_type id, std::string name) : m_id(id), m_name(name) {}
		~entity() = default;

		template<typename componentType>
		inline R_ALWAYS_INLINE componentType& addComponent();
		template<typename componentType>
		inline R_ALWAYS_INLINE componentType& addComponent(const componentType& val);

		template<typename componentType>
		inline R_ALWAYS_INLINE componentType& getComponent();

		template<typename componentType>
		inline R_ALWAYS_INLINE bool hasComponent();

		template<typename componentType>
		inline R_ALWAYS_INLINE void destroyComponent();
	};
}

#include "ecs/entity.inl"