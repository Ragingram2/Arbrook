#pragma once
#include <tuple>
#include <utility>
#include <algorithm>

#include <rsl/primitives>
#include <rsl/utilities>
#include <rsl/hash>

#include "core/ecs/entity.hpp"
#include "core/ecs/component_container.hpp"
#include "core/ecs/component_family.hpp"

namespace rythe::core::ecs
{
	//using entity_set = std::unordered_map<rsl::id_type, ecs::entity>;
	using entity_set = std::vector<ecs::entity>;
	template<typename... componentTypes>
	struct filter
	{
		using types = std::tuple<componentTypes...>;
		entity_set m_entities;

		std::tuple<ecs::component_container<componentTypes>...> m_containers;
		filter()
		{
			types t;
			std::apply([=]<typename... T>(T... args)
			{
				(
					(
						Program::Instance().m_registry->get_service<events::EventBus>()->bind<events::component_creation<decltype(args)>, filter<componentTypes...>, &filter<componentTypes...>::addEntity>(*this),
						Program::Instance().m_registry->get_service<events::EventBus>()->bind<events::component_destruction<decltype(args)>, filter<componentTypes...>, &filter<componentTypes...>::removeEntity>(*this)
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
		static constexpr std::array<rsl::id_type, sizeof...(componentTypes)> composition = { rsl::make_hash<componentTypes>()... };

		entity_set::iterator begin() noexcept;
		entity_set::iterator end() noexcept;
		entity_set::reverse_iterator rbegin() noexcept;
		entity_set::reverse_iterator rend() noexcept;
		//entity_set::reverse_itr_range reverse_range() noexcept;

		rsl::size_type size() noexcept;
		bool empty() noexcept;

		rsl::size_type count(ecs::entity val);
		bool contains(ecs::entity val);

		entity_set::iterator find(ecs::entity val);

		ecs::entity& at(rsl::size_type index);
		ecs::entity& operator[](rsl::size_type index);

		template<typename componentType>
		void addEntity(events::component_creation<componentType>& evnt);

		template<typename componentType>
		void removeEntity(events::component_destruction<componentType>& evnt);

		bool containsComp(rsl::id_type id)
		{
			for (int i = 0; i < composition.size(); i++)
				if (composition[i] == id)
					return true;
			return false;
		}

		rsl::id_type id()
		{
			return filter_id;
		}
	};
}

#include "core/ecs/filter.inl"
