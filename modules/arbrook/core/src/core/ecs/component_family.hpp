#pragma once
#include <memory>
#include <unordered_map>
#include <queue>
#include <any>

#include <rsl/primitives>
#include <rsl/hash>

#include "core/ecs/component_family_base.hpp"
#include "core/common/meta.hpp"
#include "core/events/eventbus.hpp"
#include "core/events/defaults/component_event.hpp"

namespace rythe::core::ecs
{
	using entityId = rsl::id_type;
	template<typename componentType>
	struct component_family : public component_family_base
	{
		using type = componentType;

		std::unordered_map<entityId, componentType> m_components;
		component_family() : component_family_base(rsl::type_id<componentType>()) {}
		component_family([[maybe_unused]] std::nullptr_t t) : component_family_base(0) { }
		~component_family() = default;

		virtual void reserve(rsl::size_type amount);

		virtual void clear();

		virtual pointer<void> createComponent(entityId id);

		virtual pointer<void> createComponent(entityId id, componentType&& value);

		virtual pointer<void> createComponent(entityId id, const componentType& value);


		virtual pointer<void> getComponent(entityId id);

		virtual void destroyComponent(entityId id);

	};

	template<typename componentType>
	void component_family<componentType>::reserve(rsl::size_type size)
	{
		m_components.reserve(size);
	}

	template<typename componentType>
	void component_family<componentType>::clear()
	{
		m_components.clear();
	}

	template<typename componentType>
	pointer<void> component_family<componentType>::createComponent(entityId id)
	{
		events::component_creation<componentType> compCreate{ id };
		events::EventBus::raiseEvent<events::component_creation<componentType>>(compCreate);

		m_components.try_emplace(id);

		return { &m_components.at(id) };
	}


	template<typename componentType>
	pointer<void> component_family<componentType>::createComponent(entityId id, componentType&& value)
	{
		events::component_creation<componentType> compCreate{ id };
		events::EventBus::raiseEvent<events::component_creation<componentType>>(compCreate);

		m_components.try_emplace(id);
		m_components.at(id) = value;
		return { &m_components.at(id) };
	}


	template<typename componentType>
	pointer<void> component_family<componentType>::createComponent(entityId id, const componentType& value)
	{
		events::component_creation<componentType> compCreate{ id };
		events::EventBus::raiseEvent<events::component_creation<componentType>>(compCreate);

		m_components.try_emplace(id);
		m_components.at(id) = value;
		return { &m_components.at(id) };
	}


	template<typename componentType>
	pointer<void> component_family<componentType>::getComponent(entityId id)
	{
		return { &m_components.at(id) };
	}

	template<typename componentType>
	void component_family<componentType>::destroyComponent(entityId id)
	{
		events::component_destruction<componentType> compDestruct{ id };
		events::EventBus::raiseEvent<events::component_destruction<componentType>>(compDestruct);

		m_components.erase(id);
	}
}