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
	using entity_set = rsl::hashed_sparse_set<ecs::entity>;
	template<typename... componentTypes>
	struct filter
	{
		using types = std::tuple<componentTypes...>;
		entity_set m_entities;

		std::tuple<ecs::component_container<componentTypes>...> m_containers;
		filter()
		{
			types t;
			std::apply([=,this]<typename... T>(T... args)
			{
				(
					(
						events::EventBus::bind<events::component_creation<decltype(args)>, filter<componentTypes...>, &filter<componentTypes...>::addEntity>(*this),
						events::EventBus::bind<events::component_destruction<decltype(args)>, filter<componentTypes...>, &filter<componentTypes...>::removeEntity>(*this)
						)
					, ...);
			}, t);
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
}

#include "core/ecs/filter.inl"
