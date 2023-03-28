#pragma once
#include <format>

#include <rythe/primitives>
#include <rythe/hash>

#include "core/platform/platform.hpp"
#include "core/containers/pointer.hpp"

namespace rythe::core::ecs
{
	struct entity
	{
		//ecs::entity parent;
		rsl::id_type m_id = -1;
		std::string m_name = "";

		entity() = default;
		entity(const ecs::entity& ent) : m_id(ent.m_id), m_name(ent.m_name) {}
		entity(rsl::id_type id) : m_id(id), m_name("Entity") {}
		entity(rsl::id_type id, std::string name) : m_id(id), m_name(name) {}
		~entity() = default;

		operator rsl::id_type& () { return m_id; }

		template<typename componentType>
		componentType& addComponent();

		template<typename componentType>
		componentType& getComponent();

		template<typename componentType>
		bool hasComponent();

		template<typename componentType>
		void destroyComponent();

		bool operator==(const entity& other) {
			return m_id == other.m_id;
		}


		entity& operator=(const entity & other) {
			m_id = other.m_id;
			m_name = other.m_name;
			return *this;
		}
	};
}

#include "core/ecs/entity.inl"