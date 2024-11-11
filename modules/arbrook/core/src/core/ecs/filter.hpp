#pragma once
#include <tuple>
#include <map>
#include <utility>
#include <algorithm>

#include <rsl/primitives>
#include <rsl/utilities>
#include <rsl/hash>
#include <rsl/containers>

#include "core/ecs/entity.hpp"
#include "core/ecs/component_container.hpp"
#include "core/ecs/component_family.hpp"

namespace rythe::core::ecs
{

	template<typename componentType, typename... others>
	static void bind_events()
	{
		//events::EventBus::bind<events::component_creation<componentType>, decltype(filter), &decltype(filter)::addEntity>(&filter);
		//events::EventBus::bind<events::component_destruction<componentType>, decltype(filter), &decltype(filter)::removeEntity>(&filter);
		if constexpr (sizeof...(others) != 0)
		{
			bind_events<others...>();
		}
	}

	using entity_set = rsl::hashed_sparse_set<ecs::entity>;
	template<typename... componentTypes>
	struct filter
	{
		using types = std::tuple<componentTypes...>;
		entity_set m_entities;

		std::tuple<ecs::component_container<componentTypes>...> m_containers;
		filter()
		{

			bind_events<componentTypes...>();
			//types t;
			//std::apply([=]<typename... T>(T... args)
			//{
			//	(
			//		(
			//			events::EventBus::bind<events::component_creation<decltype(args)>, filter<componentTypes...>, &filter<componentTypes...>::addEntity>(*this),
			//			events::EventBus::bind<events::component_destruction<decltype(args)>, filter<componentTypes...>, &filter<componentTypes...>::removeEntity>(*this)
			//			)
			//		, ...);
			//}, t);
		}

	private:

		template<typename componentType>
		static constexpr rsl::id_type generateId()
		{
			return rsl::typeHash<componentType>();
		}

		template<typename componentType0, typename componentType1, typename... componentTypeN>
		static constexpr rsl::id_type generateId()
		{
			return rsl::combine_hash(rsl::make_hash<componentType0>(), generateId<componentType1, componentTypeN...>());
		}
	public:
		static constexpr rsl::id_type filter_id = generateId<componentTypes...>();
		static constexpr std::array<rsl::id_type, sizeof...(componentTypes)> composition = { rsl::typeHash<componentTypes>()... };

		entity_set::iterator begin() noexcept;
		entity_set::iterator end() noexcept;
		entity_set::reverse_iterator rbegin() noexcept;
		entity_set::reverse_iterator rend() noexcept;
		//entity_set::reverse_itr_range reverse_range() noexcept;

		rsl::size_type size() noexcept;
		bool empty() noexcept;

		rsl::size_type count(ecs::entity val);
		bool containsEntity(ecs::entity val);
		bool containsEntity(rsl::id_type val);

		entity_set::iterator find(ecs::entity val);
		entity_set::iterator find(rsl::id_type val);

		ecs::entity& at(rsl::size_type index);
		ecs::entity& operator[](rsl::size_type index);

		template<typename componentType>
		void addEntity(events::component_creation<componentType>& evnt);

		template<typename componentType>
		void removeEntity(events::component_destruction<componentType>& evnt);

		template<typename componentType>
		ecs::component_container<componentType> getContainer()
		{
			return std::get<ecs::component_container<componentType>>(m_containers);
		}

		bool contains(const std::unordered_set<rsl::id_type>& comp)
		{
			if (!comp.size())
				return false;

			if (!composition.size())
				return true;

			for (auto& typeId : composition)
				if (!comp.count(typeId))
					return false;
			return true;
		}

		rsl::id_type id()
		{
			return filter_id;
		}
	};

	template<typename... componentTypes>
	inline entity_set::iterator filter<componentTypes...>::begin() noexcept
	{
		return m_entities.begin();
	}

	template<typename... componentTypes>
	inline entity_set::iterator filter<componentTypes...>::end() noexcept
	{
		return m_entities.end();
	}

	template<typename... componentTypes>
	inline entity_set::reverse_iterator filter<componentTypes...>::rbegin() noexcept
	{
		return m_entities.rbegin();
	}

	template<typename... componentTypes>
	inline entity_set::reverse_iterator filter<componentTypes...>::rend() noexcept
	{
		return m_entities.rend();
	}

	template<typename... ComponentTypes>
	inline rsl::size_type filter<ComponentTypes...>::size() noexcept
	{
		return m_entities.size();
	}

	template<typename... ComponentTypes>
	inline bool filter<ComponentTypes...>::empty() noexcept
	{
		return m_entities.empty();
	}

	template<typename... ComponentTypes>
	inline rsl::size_type filter<ComponentTypes...>::count(entity val)
	{
		auto position = std::find(m_entities.begin(), m_entities.end(), val);
		return position != m_entities.end();
	}

	template<typename... ComponentTypes>
	inline bool filter<ComponentTypes...>::containsEntity(entity val)
	{
		auto position = std::find(m_entities.begin(), m_entities.end(), val);
		return position != m_entities.end();
	}

	template<typename... ComponentTypes>
	inline bool filter<ComponentTypes...>::containsEntity(rsl::id_type val)
	{
		auto position = std::find(m_entities.begin(), m_entities.end(), ecs::Registry::entities[val]);
		return position != m_entities.end();
	}


	template<typename... ComponentTypes>
	inline entity_set::iterator filter<ComponentTypes...>::find(entity val)
	{
		return std::find(m_entities.begin(), m_entities.end(), val);
	}

	template<typename... ComponentTypes>
	inline entity_set::iterator filter<ComponentTypes...>::find(rsl::id_type val)
	{
		return std::find(m_entities.begin(), m_entities.end(), ecs::Registry::entities[val]);
	}

	template<typename... ComponentTypes>
	inline entity& filter<ComponentTypes...>::at(rsl::size_type index)
	{
		return m_entities.at(index);
	}

	template<typename... ComponentTypes>
	inline entity& filter<ComponentTypes...>::operator[](rsl::size_type index)
	{
		return m_entities.at(index);
	}

	template<typename... componentTypes>
	template<typename componentType>
	inline void filter<componentTypes...>::addEntity(events::component_creation<componentType>& evnt)
	{
		if (!containsEntity(evnt.entId) && contains(ecs::Registry::entityCompositions[evnt.entId]))
		{
			m_entities.emplace(entity{ &ecs::Registry::entities[evnt.entId] });
		}
	}

	template<typename... componentTypes>
	template<typename componentType>
	inline void filter<componentTypes...>::removeEntity(events::component_destruction<componentType>& evnt)
	{
		auto position = find(evnt.entId);
		if (position != m_entities.end())
		{
			auto id = position - m_entities.begin();
			m_entities.erase(m_entities[id]);
		}
	}

}

//#include "core/ecs/filter.inl"
